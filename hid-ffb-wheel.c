#include <linux/init.h>
#include <linux/module.h>
#include <linux/hid.h>
#include <linux/usb.h>

#include "hid-ffb-wheel.h"

static const struct hid_device_id ffb_wheel_id_table[] = {
    { HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY, HID_ANY_ID, HID_ANY_ID) },
};


static int ffb_wheel_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	return 0;
}

static int ffb_wheel_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *rd, int size)
{

	return 0;
}

static int ffb_wheel_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	struct usb_interface *iface;
	__u8 iface_num;
	struct ffb_wheel_drv_data *drv_data;
	int ret;

	if (!hid_is_usb(hdev))
		return -EINVAL;

	iface = to_usb_interface(hdev->dev.parent);
	iface_num = iface->cur_altsetting->desc.bInterfaceNumber;

	drv_data = kzalloc(sizeof(struct ffb_wheel_drv_data), GFP_KERNEL);
	if (!drv_data) {
		hid_err(hdev, "Insufficient memory, cannot allocate driver data\n");
		return -ENOMEM;
	}

	hid_set_drvdata(hdev, (void *)drv_data);

	return 0;

err_stop:
	hid_hw_stop(hdev);
err_free:
	kfree(drv_data);
	return ret;
}

static void ffb_wheel_remove(struct hid_device *hdev)
{
	void *drv_data = hid_get_drvdata(hdev);
	hid_hw_stop(hdev);
	kfree(drv_data);
}

MODULE_DEVICE_TABLE(ffb_driver, ffb_wheel_id_table);

static struct hid_driver ffb_driver = {
	.name = "ffb_driver",
	.id_table = ffb_wheel_id_table,
	.event = ffb_wheel_event,
	.raw_event = ffb_wheel_raw_event,
	.probe = ffb_wheel_probe,
	.remove = ffb_wheel_remove,
};

module_hid_driver(ffb_driver);

#define PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP

int fbb_usb_vendor_id = 1003;
module_param_named(fbb_usb_vendor_id, fbb_usb_vendor_id, int, PERM);

MODULE_DESCRIPTION("Force Feedback driver for custom STM32 steering wheel");
MODULE_LICENSE("GPL");
