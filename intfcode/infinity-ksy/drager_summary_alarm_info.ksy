meta:
  id: drager_summary_alarm_info
  endian: be
seq:
  - id: alarm_blocks
    type: alarm_block
    repeat: eos
types:
  alarm_block:
    seq:
      - id: alarm_limit
        type: u2
      - id: alarm_timestamp
        size: 6
      - id: current_alarm_tone_grade
        type: u1
      - id: signal_group
        type: u1
      - id: param_id
        type: u1
      - id: alarm_condition
        type: u1
      - id: alarm_state
        type: u1
      - id: alarm_grade
        type: u1
      - id: is_flashing
        type: u1
      - id: foreground_color
        type: u1
      - id: background_color
        type: u1