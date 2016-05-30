#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* endpoints enumeration */
#define ENDP0       ((uint8_t)0)
#define ENDP1       ((uint8_t)1)
#define ENDP2       ((uint8_t)2)
#define ENDP3       ((uint8_t)3)
#define ENDP4       ((uint8_t)4)
#define ENDP5       ((uint8_t)5)
#define ENDP6       ((uint8_t)6)
#define ENDP7       ((uint8_t)7)

enum RECIPIENT_TYPE
{
  DEVICE_RECIPIENT,     /* Recipient device    */
  INTERFACE_RECIPIENT,  /* Recipient interface */
  ENDPOINT_RECIPIENT,   /* Recipient endpoint  */
  OTHER_RECIPIENT
};

enum DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIG_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR
};

#define REQUEST_DIR       0x80  /* Mask to get request dir  */
#define REQUEST_TYPE      0x60  /* Mask to get request type */
#define STANDARD_REQUEST  0x00  /* Standard request         */
#define CLASS_REQUEST     0x20  /* Class request            */
#define VENDOR_REQUEST    0x40  /* Vendor request           */
#define RECIPIENT         0x1F  /* Mask to get recipient    */

#define USB_SETUP_SET(req) ((req & REQUEST_DIR) == 0)
#define USB_SETUP_GET(req) ((req & REQUEST_DIR) != 0)

enum
{
  USB_UNSUPPORT = 0,
  USB_SUCCESS = 1,
};

struct req_args {
  uint16_t value;
  uint16_t index;
  uint16_t len;
};

void usb_cb_device_reset (void);
int usb_cb_setup (uint8_t req, uint8_t req_no, struct req_args *arg);
int usb_cb_interface (uint8_t cmd, struct req_args *arg);
int usb_cb_get_descriptor (uint8_t rcp, uint8_t desc_type, uint8_t desc_index,
			   struct req_args *arg);
int usb_cb_handle_event (uint8_t event_type, uint16_t value);
void usb_cb_ctrl_write_finish (uint8_t req, uint8_t req_no,
			       struct req_args *arg);
void usb_cb_tx_done (uint8_t ep_num);
void usb_cb_rx_ready (uint8_t ep_num);

enum {
  USB_EVENT_ADDRESS,
  USB_EVENT_CONFIG,
  USB_EVENT_SUSPEND,
  USB_EVENT_WAKEUP,
  USB_EVENT_STALL,
};

enum {
  USB_SET_INTERFACE,
  USB_GET_INTERFACE,
  USB_QUERY_INTERFACE,
};

enum DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  SUSPENDED,
  ADDRESSED,
  CONFIGURED
};

void usb_lld_init (uint8_t feature);

int usb_lld_reply_request (const void *buf, size_t buflen,
			   struct req_args *arg);
void usb_lld_set_data_to_recv (void *p, size_t len);

void usb_lld_tx_enable (uint8_t ep_num, const void *buf, size_t len);
int usb_lld_tx_result (int ep_num);

void usb_lld_rx_enable (int ep_num, void *buf, size_t len);
int usb_lld_rx_data_len (int ep_num);

void usb_lld_stall (int ep_num);

void usb_lld_reset (uint8_t feature);
void usb_lld_setup_endpoint (int n, int rx_en, int tx_en);
void usb_lld_set_configuration (uint8_t config);
uint8_t usb_lld_current_configuration (void);

void usb_lld_prepare_shutdown (void);
void usb_lld_shutdown (void);

void usb_interrupt_handler (void);