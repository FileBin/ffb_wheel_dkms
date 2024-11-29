#include "hid-ffb-wheel.h"

void init_hid_safe_report(hid_safe_report *this, struct hid_report *report) {
  spin_lock_init(&this->report_lock);
  this->report = report;
}
