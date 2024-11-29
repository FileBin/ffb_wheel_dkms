#include <linux/hid.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>

#include "hid-ffb-wheel.h"
#include "linux/hid.h"
#include "linux/input.h"
#include "linux/list.h"
#include "linux/types.h"
#include "pid-descriptor-parser.h"
#include "pid_def.h"

static const struct hid_device_id ffb_wheel_id_table[] = {
    {HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY, HID_ANY_ID, HID_ANY_ID)},
};

static int ffb_wheel_upload(struct input_dev *dev, struct ff_effect *effect,
                     struct ff_effect *old) {
  struct hid_device *hid = input_get_drvdata(dev);

  const ffb_wheel_ffb_data* data = dev->ff->private;

  struct hid_report report;

  hid_hw_request(hid, 0, HID_REQ_SET_REPORT) ;
  return 0;
}

static int ffb_wheel_erase(struct input_dev *dev, int effect_id) { return 0; }

static int ffb_wheel_playback(struct input_dev *dev, int effect_id, int value) {
  return 0;
}

static void ffb_wheel_set_gain(struct input_dev *dev, u16 gain) {

}

static int ffb_wheel_probe(struct hid_device *hdev,
                           const struct hid_device_id *id) {
  int ret;

  if (!hid_is_usb(hdev))
    return -EINVAL;

  if (list_empty(&hdev->inputs)) {
    hid_err(hdev, "no inputs found\n");
    return -ENODEV;
  }
  struct hid_input *hidinput =
      list_entry(hdev->inputs.next, struct hid_input, list);
  struct input_dev *dev = hidinput->input;

  ret = hid_ffb_wheel_parse_descriptor(hdev, dev);

  if (ret) {
    goto err_exit;
  }

  dev->ff->upload = ffb_wheel_upload;
  dev->ff->erase = ffb_wheel_erase;
  dev->ff->playback = ffb_wheel_playback;
  dev->ff->set_gain = ffb_wheel_set_gain;

  return 0;

err_stop:
  hid_hw_stop(hdev);
err_exit:
  return ret;
}

static void ffb_wheel_remove(struct hid_device *hdev) { hid_hw_stop(hdev); }

MODULE_DEVICE_TABLE(ffb_driver, ffb_wheel_id_table);

static struct hid_driver ffb_driver = {
    .name = "ffb_driver",
    .id_table = ffb_wheel_id_table,
    .probe = ffb_wheel_probe,
    .remove = ffb_wheel_remove,
};

module_hid_driver(ffb_driver);

MODULE_DESCRIPTION("Force Feedback driver for custom steering wheels");
MODULE_LICENSE("GPL");
