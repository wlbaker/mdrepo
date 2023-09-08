meta:
  id: pnmwav
  file-extension: pnmwav
  encoding: utf-8
  endian: le

enums:
  filetag:
    5000: ft_header_begin
    5001: ft_header_end
    5002: ft_file_version
    5003: ft_channel_list_ptr
    5004: ft_block_list_ptr
    
    5005: ft_chan_list_begin
    5006: ft_chan_list_end
    5007: ft_chan_begin
    5008: ft_chan_end
    5009: ft_chan_id_int
    
    5010: ft_data_block_begin
    5011: ft_data_block_end
    5012: ft_ticks_per_sample
    5013: ft_start_time
    5014: ft_end_time
    5015: ft_data_chunk
  
    5016: ft_block_list_begin
    5017: ft_block_list_end
    5018: ft_block_entry_begin
    5019: ft_block_entry_end
    5020: ft_block_ptr
    
    5021: ft_unused3
    
    5022: ft_storage_info_begin
    5023: ft_storage_info_type
    5024: ft_storage_info_end
    
    5025: ft_ad_low
    5026: ft_ad_high
    5027: ft_unused1
    5028: ft_unused2
    5029: ft_lowscale
    5030: ft_highscale

    5031: ft_super_index_begin
    5032: ft_super_segment_begin
    5033: ft_super_segment_end
    5034: ft_super_index_ptr
    5035: ft_super_entry_begin
    5036: ft_super_entry_end
    5037: ft_super_index_end

    5038: ft_earliest_file_time
    5039: ft_latest_file_time
    5040: ft_subject_id_int
    5041: ft_subject_name
    5042: ft_local_time_zone_id
    5043: ft_acq_successfully_completed
    5044: ft_subject_id
    5045: ft_channel_id

seq:
  - id: magic
    contents: [0xaf, 0x55, 0x55, 0xaa]
  - id: header
    type: pnm_header
  - id: channel_tags
    type: pnm_taglist
    
types:
  pnm_header:
    seq:
    - id: header_start
      contents: [0x88, 0x13]
    - id: header_len
      type: u4
    - id: header_end
      type: u8
      # dataloc is a computed field: first_tag.dataloc + 8 + _io.pos
    - id: header_payload
      size: header_end - _io.pos
      type: pnm_taglist
#      # size: header_end
      
  pnm_tag:
    seq:
      - id: tag_id
        type: u2
        enum: filetag
      - id: tag_len
        type: u4
      - id: payload
        size: tag_len
        type:
          switch-on: tag_id
          cases:
            'filetag::ft_file_version': u4
            # 'filetag::ft_channel_list_ptr': pnm_channel_ptr
            'filetag::ft_block_list_ptr': u8
            'filetag::ft_super_index_ptr': u8
            'filetag::ft_earliest_file_time': u8  # tick = 1/10000 of milli
            'filetag::ft_latest_file_time': u8  # tick = 1/10000 of milli
            'filetag::ft_subject_id_int': u4
            'filetag::ft_subject_id': u8
            'filetag::ft_subject_name': str
            'filetag::ft_local_time_zone_id': str
            'filetag::ft_acq_successfully_completed': u4
            'filetag::ft_channel_id': u8
            'filetag::ft_chan_begin': u8
            'filetag::ft_ad_low': s2
            'filetag::ft_lowscale': f4
            'filetag::ft_highscale': f4
            'filetag::ft_ad_high': s2
            'filetag::ft_block_entry_begin': u8
            'filetag::ft_block_ptr': u8
            'filetag::ft_start_time': u8
            'filetag::ft_end_time': u8
            'filetag::ft_ticks_per_sample': u8
            'filetag::ft_storage_info_begin': u8
            'filetag::ft_storage_info_type': u4
            'filetag::ft_data_block_begin': u8
            'filetag::ft_data_chunk': pnm_datachunk
            
  pnm_datachunk:
    seq:
    - id: v
      type: s2
      repeat: eos
      
  pnm_taglist:
    seq:
    - id: tags
      type: pnm_tag
      repeat: eos

  pnm_channel_ptr:
    seq:
    - id: channel_desc_offset
      type: u8
    instances:
      channel_list:
        pos: channel_desc_offset
        size: 100
        
