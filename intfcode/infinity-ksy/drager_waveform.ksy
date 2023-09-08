doc: |
  This parses the Drager Waveform Data

meta:
  id: drager_waveform
  endian: be
seq:
  - id: wvf
    type: u2
  - id: n_waves
    type: u1
  - id: channel_id
    type: u1
  - id: dhdl
    type: u2
  - id: rnrd
    type: u2
  - id: waveform_blocks
    type: wave_block
    repeat: expr
    repeat-expr: n_waves
types:
  wave_block:
    seq:
      - id: sample_rate
        type: u2
      - id: block_len
        type: u2
      - id: timestamp
        type: u4
      - id: not_sure
        type: u1
      - id: partial_timestamp
        type: u1
      - id: signal_group
        type: u1
        enum: signal_group_codes
      - id: signal_id
        type: u1
        enum: signal_id_codes
      - id: n_samples
        type: u1
      - id: spare
        type: u1
      - id: wvf_data
        type: s2
        repeat: expr
        repeat-expr: n_samples
enums:
  signal_group_codes:
    0: invalid
    1: ecg
    2: resp
    3: art
    4: pa
    5: icp
    6: cvp
    7: la
    8: ra
    9: lv
    10: rv
    11: gp1
    12: gp2
    13: p1a
    14: p1b
    15: p1c
    16: p1d
    17: p2a
    18: p2b
    19: p2c
    20: p2d
    21: p3a
    22: p3b
    23: p3c
    24: p3d
    25: spo2
    26: tbasic
    27: temp1
    28: temp2
    29: temp3
    30: nibp
    31: a2co2
    32: co
    33: ibp
    34: alarm
    35: mib_svo2
    36: mib_vent
    37: mgm_co2
    38: mgm_o2
    39: mgm_n2o
    40: mgm_agent
    41: svo2
    42: eeg
    43: vent
    44: crg
    45: gas
    46: tcpo2
    47: o2p
    48: n2op
    49: airp
    50: mip_pao2
    51: vcalc
    52: p1
    53: p2
    54: nco
    55: tcp
    56: tcp2
    57: fio2
    58: trend
    59: eeg1
    60: eeg2
    61: eeg3
    62: eeg4
    63: awco2
    64: icp2
    65: bis
    66: labdat
    67: ventset
    68: spo2athena
    69: nmt
    70: fasttemp
    71: cncco
    72: cnap
    73: pic
  signal_id_codes:
    0: invalid
    1: none
    2: lead_1
    3: lead_2
    4: lead_3
    5: lead_avr
    6: lead_avf
    7: lead_avl
    8: lead_v1
    9: lead_mcl1
    10: lead_mcl6
    11: lead_ra
    12: lead_la
    13: lead_ll
    14: lead_rl
    15: lead_vl
    16: temp_a
    17: temp_b
    18: co_blood
    19: co_inj
    20: ir
    21: red
    22: pulse
    23: cascade
    24: raw_cuff
    25: lp_cuff
    26: pulse_ext
    27: press
    28: flow
    29: hal
    30: iso
    31: enf
    32: sev
    33: des
    34: lead_v_prime
    35: dr
    36: lead_v
    37: lead_v2
    38: lead_v3
    39: lead_v4
    40: lead_v5
    41: lead_v6
    42: vol
    43: lead_dv1
    44: lead_dv2
    45: lead_dv3
    46: lead_dv4
    47: lead_dv5
    48: lead_dv6
    49: eeg1
    50: eeg2
    51: lead_avr_imv
    52: last