#include "linux/hid.h"
#include "linux/input.h"
#include "linux/types.h"
#include "pid-descriptor-parser.h"

/**
 * parses data from a PID device
 * @param  hdev:
 * @param  data:
 * @retval max_effects_count if success, < 0 on error
 */

int hid_ffb_wheel_parse_descriptor(struct hid_device *hdev,
                                   struct input_dev *idev) {

  ffb_wheel_ffb_data *ffb_data =
      kzalloc(sizeof(ffb_wheel_ffb_data), GFP_KERNEL);

  int max_effects = 0;
  if (!ffb_data) {
    hid_err(hdev, "Insufficient memory, cannot allocate driver data\n");
    return -ENOMEM;
  }

  struct list_head *report_list =
      &hdev->report_enum[HID_OUTPUT_REPORT].report_list;

  struct list_head *i_list;
  struct list_head *j_list;
  list_for_each(i_list, report_list) {
    struct hid_report *report = list_entry(i_list, struct hid_report, list);
    if (report->type != HID_OUTPUT_REPORT)
      continue;

    switch (report->application) {
    case 0xAB: /* CREATE_NEW_EFFECT_REPORT */
      init_hid_safe_report(&ffb_data->reports.create_new_effect, report);

      list_for_each(j_list, &report->field_entry_list) {
        struct hid_field *field = list_entry(j_list, struct hid_field_entry, list)->field;

        if (field->usage->hid != 0x25)
          continue;

        // if(field->usage->hid)
      }
      break;
    }
  }

  input_ff_create(idev, max_effects);

  idev->ff->private = ffb_data;

  return 0;
}
