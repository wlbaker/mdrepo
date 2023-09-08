meta:
  id: drager_param_and_alarm
  endian: be
seq:
  - id: num_params
    type: u1
  - id: bytes_per_param
    type: u1
  - id: param_alarm_blocks
    type: param_alarm_block
    repeat: eos
types:
  param_alarm_block:
    seq:
      - id: param_val
        type: u2
      - id: param_upper_limit
        type: u2
      - id: param_lower_limit
        type: u2
      - id: alarm_limit
        type: u2
      - id: param_timestamp
        size: 6
      - id: alarm_timestamp
        size: 6
      - id: signal_group
        type: u1
      - id: param_id
        type: u1
      - id: param_val_id
        type: u1
      - id: alarm_attrib
        type: u1
      - id: unit_of_measure
        type: u1
      - id: units_exp
        type: u1
      - id: show_units
        type: u1
      - id: alarm_condition
        type: u1
      - id: alarm_state
        type: u1
      - id: alarm_grade
        type: u1
      - id: curr_param_color
        type: u1
      - id: default_param_color
        type: u1
      - id: limits_type
        type: u1
      - id: background_color
        type: u1
      - id: is_flashing
        type: u1
      - id: num_decimals_to_display
        type: u1