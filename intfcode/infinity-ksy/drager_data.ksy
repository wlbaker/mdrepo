meta:
  id: drager_data
  endian: be
  imports:
    - drager_waveform
    - drager_display_setup
    - drager_summary_alarm_info
    - drager_param_and_alarm
seq:
  - id: ndo_id
    type: u2
  - id: pad
    type: u2
  - id: msg_seq
    type: u4
  - id: unix_timestamp
    type: u4
  - id: device_ip
    size: 4
  - id: connect_id
    type: u2
  - id: unknown_timestamp
    type: u2
  - id: not_sure0
    type: u4
  - id: major_version
    type: u2
  - id: minor_version
    type: u2
  - id: num_bytes
    type: u1
  - id: num_ndos
    type: u1
    doc: |
         Note that this field includes the first setup ndo, so there
         will be num_ndos-1 ndo_blocks.
  - id: spare
    type: u2
  - id: ndo_blocks
    type: ndo_block
    repeat: eos
types:
  ndo_block:
    seq:
      - id: ndo_id
        type: u2
        enum: ndo_ids
      - id: n_bytes
        type: u2
      - id: body
        size: n_bytes > 4 ? (n_bytes-4) : n_bytes
        type:
          switch-on: ndo_id
          cases:
            'ndo_ids::display_setup': drager_display_setup
            'ndo_ids::waveform': drager_waveform
            'ndo_ids::summary_alarm_info': drager_summary_alarm_info
            'ndo_ids::parameter_and_alarm': drager_param_and_alarm
            _: arb
  arb:
    seq:
      - id: stuff
        size-eos: True

enums:
  ndo_ids:
    10: bed_config
    11: display_setup
    12: waveform
    13: waveform_setup
    14: parameter_and_alarm
    15: parameter_measurement_time
    16: parameter_box_setup
    17: signal_group_interval_measurement
    18: current_msg_displayed
    19: cps_device_status
    20: summary_alarm_info
    21: qrs_blip
    22: pls_sig
    23: pat_loc
    24: vent_current_msg
    25: vent_wv_desc
    26: vent_param_list
    27: vent_vol_wv_desc
    28: pds_28
    34: pds_34