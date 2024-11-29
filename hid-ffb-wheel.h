#include "asm-generic/int-ll64.h"

#ifndef HID_FFB_WHEEL_H_
#define HID_FFB_WHEEL_H_

typedef struct {
  int logical_minimum;
  int logical_maximum;
  u8 offset;
  u8 size;
} logical_field;

typedef struct {
  logical_field f;
  s8 et_constant_force_id;
  s8 et_ramp_id;
  s8 et_square_id;
  s8 et_sine_id;
  s8 et_triangle_id;
  s8 et_sawtooth_up_id;
  s8 et_sawtooth_down_id;
  s8 et_spring_id;
  s8 et_damper_id;
  s8 et_inertia_id;
  s8 et_friction_id;
} effect_type;

typedef struct {
  logical_field f;
  s8 exponent;
} time_field;

typedef struct {
  u8 report_id;
  u8 size;
} report_info;

typedef struct {
  report_info info;
  
  effect_type effect_type;
  logical_field byte_count;
} create_new_effect_mapping;

typedef struct {
  report_info info;

  logical_field effect_block_index;
  effect_type effect_type;
  time_field duration;
  time_field sample_period;
  logical_field gain;
} set_effect_report_mapping;

typedef struct {
  report_info info;

  logical_field effect_block_index;
  logical_field attack_level;
  time_field attack_time;
  logical_field fade_level;
  time_field fade_time;
} set_envelope_report_mapping;

typedef struct {
  report_info info;

  logical_field effect_block_index;
  logical_field cp_offset;
  logical_field dead_band;
  logical_field positive_coefficient;
  logical_field negative_coefficient;
  logical_field positive_saturation;
  logical_field negative_saturation;

} set_condition_report_mapping;

typedef struct {
  create_new_effect_mapping create_new_effect_mapping;
  set_effect_report_mapping set_effect_report_mapping;
  set_envelope_report_mapping set_envelope_report_mapping;
} report_mapping;

typedef struct {
  report_mapping report_mapping;
} ffb_wheel_ffb_data;

#endif // HID_FFB_WHEEL_H_
