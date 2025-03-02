#include <linux/hid.h>
#include "hid-ffb-wheel.h"

#ifndef PID_DESCRIPTOR_PARSER_H_
#define PID_DESCRIPTOR_PARSER_H_

int hid_ffb_wheel_parse_descriptor(struct hid_device* hdev, struct input_dev * idev);

#endif // PID_DESCRIPTOR_PARSER_H_
