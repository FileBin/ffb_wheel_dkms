#include "asm-generic/int-ll64.h"
#include "linux/hid.h"
#include "linux/spinlock_types.h"

#ifndef HID_FFB_WHEEL_H_
#define HID_FFB_WHEEL_H_

typedef struct {
  spinlock_t report_lock; /* Protect output HID report */
  struct hid_report *report;
} hid_safe_report;

void init_hid_safe_report(hid_safe_report * this, struct hid_report* report);

typedef struct {
  struct {
    hid_safe_report create_new_effect;
  } reports;
} ffb_wheel_ffb_data;

#endif // HID_FFB_WHEEL_H_
