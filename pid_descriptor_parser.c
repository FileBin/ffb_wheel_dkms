#include "linux/input.h"
#include "pid-descriptor-parser.h"

/**
 * parses data from a PID device
 * @param  hdev:
 * @param  data:
 * @retval max_effects_count if success, < 0 on error
 */

int hid_ffb_wheel_parse_descriptor(struct hid_device *hdev,
                                   struct input_dev *idev) {

  ffb_wheel_ffb_data* ffb_data = kzalloc(sizeof(ffb_wheel_ffb_data), GFP_KERNEL);

  int max_effects = 0;
  if (!ffb_data) {
    hid_err(hdev, "Insufficient memory, cannot allocate driver data\n");
    return -ENOMEM;
  }

  input_ff_create(idev, max_effects);

  idev->ff->private = ffb_data;

  return 0;
}
