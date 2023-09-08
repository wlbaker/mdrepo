
#include <arpa/inet.h>
#include <stdio.h>

#include "infinityNet.h"
#include "log.h"
#include "bytebuffer.h"
#include "pista.h"
#include "infinity.pb-c.h"

#define DEBUG

static char * sig_gr_codes[] = { //
            "invalid", //
            "ecg", "resp", "art", "pa", "icp", "cvp", "la", "ra", "lv", "rv", // 10
            "gp1", "gp2", //
            "p1a", "p1b", "p1c", "p1d", //
            "p2a", "p2b", "p2c", "p2d", //
            "p3a", "p3b", "p3c", "p3d", //
            "spo2", // 25
            "tbasic", //
            "temp1", "temp2", "temp3", //
            "nibp", // 30
            "a2co2", "co", "ibp", "alarm", //
            "mib_svo2", "mib_vent", //
            "mgm_co2", //
            "mgm_o2", "mgm_n2o", "mgm_agent", // 40
            "svo2", "eeg", "vent", "crg", "gas", //
            "tcpo2", "o2p", "n2op", "airp", "mib_pao2", // 50
            "vcalc", "p1", "p2", "nco", "tcp", "tcp2", "fio2", "trend", "eeg1", "eeg2", "eeg3", "eeg4", // 62
            "awco2", "icp2", "bis", "labdat", "ventset", "spo2athena", "nmt", "fasttemp", // 70
            "cncco", "cnap", "pic", "74", "75", "76", "77", "78", "79", "80", // 80
            "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", //
            "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", //
            "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", //
            "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", //
            "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", //
    };

static char * sig_id_codes[] = { //
            "invalid", //
            NULL, // only one in group...don't add extension
            "lead_I", "lead_II", "lead_III", "lead_AVR", "lead_AVF", "lead_AVL", "lead_V1", "lead_MCL1", "lead_MCL6", //
            "lead_RA", "lead_LA", "lead_LL", "lead_RL", "lead_VL", //
            "temp_a", "temp_b", //
            "co_blood", "co_inj", //
            "ir", "red", "pulse", // spo2
            "cascade", // ecg
            "raw_cuff", "lp_cuff", "pulse_ext", // nibp
            "press", "flow", "hal", "iso", "enf", "sev", "des", // agent...anestesia?
            "lead_v_prime", // ecg
            "dr", // nco
            "lead_V", "lead_V2", "lead_V3", "lead_V4", "lead_V5", "lead_V6", // ecg
            "vol", //
            "lead_DV1", "lead_DV2", "lead_DV3", "lead_DV4", "lead_DV5", "lead_DV6", // ecg
            // derived
            "eeg1", "eeg2", // eeg
            "lead_avr_imv", // ecg
            "last" };

static char *param_codes[] = { //
            "invalid", //
            "hr", "pp", "arr", "pvc", "pr", "rr", "dia", "sys", "mean", "cpp", // 10
            "a", "b", "delta", "satu", "etco2", "ico2", "co", "co_avg", "ti", "tb", // 20
            "pwp", "sa1", "svo2", "sao2", "cco", "cci", "ico", "ici", "svr", "svri", // 30
            "do2", "vo2", "sv", "sqi", "ref", "pap", "peep", "map", "mv", "tv", // 40
            "pause", "ieratio", "eto2", "io2", "etn2o", "in2o", "ethal", "ihal", "etiso", "iiso", // 50
            "etenf", "ienf", "etsev", "isev", "etdes", "ides", "st1", // ECG
                                                                        // starts
                                                                        // here
                                                                        // -- 57
            "st2", "st3", "stavr", // 60
            "stavf", "stavl", "stv1", "mcl1", "mcl6", "st", "mvi", "tvi", "wallp", "tankp", // 70
            "pvr", "pvri", "svi", "tvr", "tpr", "lvsw", "lvswi", "rvsw", "rvswi", "lhcpp", // 80
            "rpi", "pao2", "pvo2", "paco2", //
            "vco2", //
            "cao2", "cvo2", "avdo2", "do2i", "vo2i", // vent calcs
            "o2er", "aado2", "qsqt", "cdyn", //
            "cs", "ri", "re", "eef", "vd", "vtp_ration", "vta_ratio", "alvent", "wob", // end
            // vent
            // calcs
            "st_vprime", "nco", "nsv", "stv2", "stv3", "stv4", "stv5", "stv6", "stv", "stvm", "stcvm", "stx", "sty",
            "stz", "o2", "co2", "htrpwr", "stlead", "nosubscript", "trendmarker", "median", "sef", "bsr", "tot_pwr",
            "beta_pwr", "alpha_pwr", "theta_pwr", "delta_pwr", "pip", "tvi_mech", "tvi_spon", "tva", "tot_mv", "mva",
            "mv_spon", "vd_aw", "c_dyn", "c_stat", "c2o_dyn", "eraw", "iraw", "wo_bimp", "vd_vt", "vd_phy", "vol_delta",
            "pleth", "pplat", "bis", "emg", "sr", "power", "ipeep", "pif", "pef", "tve_mech", "tve_spon", "mve_mech",
            "mve_spon", "rr_mech", "rr_spon", "c_total", "rsbi", "wob_mech", "tv_ratio", "mvco2", "tvco2", "tva_spon",
            "tva_mech", "mva_spon", "mva_mech", "peco2", "dilut_ratio_aw", "insp_time", "exp_time", "insp_time_pct",
            "tv_leak", "mv_pct", "ph", "hco3", "hct", "hgb", "raw", //
            "deriv_v1", "deriv_v2", "deriv_v3", "deriv_v4", "deriv_v5", "deriv_v6", "current", "twitch", //
            "tof_ratio", "tof_count", "pct_count", "temp", "bct", "mac", "bat", "pco", //
            "gedv", "gedvi", "evlw", "evlwi", "gef", "pbt", "pvpi", "pcco", "pcci", "psvi", "svv", //
            "psvr", "psvri", "dpmax", "edv", "esv", "esvi", "ef", "tair", "t1skin", "t2skin", "wt", //
            "rh", "pcto2", "tmatt", "pwrhtr", "tair_set", "tskin_set", "rh_set", "o2_set", "tmatt_set", "etvi", "234",
            "235", "236", "237", "238", "239", //
            "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", //
            "250", "251", "252", "253", "254", "255" //
    };

static struct pista_item_desc *findMetric(int sig_group, int sig_id ) {
    return NULL;
}

char opmode;
char horiz_pboxes;
int  tick = 0;

static void getTimestamp(byte_buffer_t *ndo_buffer) {
    for (int i = 0; i < 6; i++) {
        bb_get( ndo_buffer );
    }

    return; // ts
}

static void getFixedLengthString(char *dest, byte_buffer_t *ndo_buffer, int sz) {
        char message[sz+1];
        for (int i = 0; i < sz; i++) {
            char ch = bb_get_short(ndo_buffer);
            message[i] = ch;
        }
        message[sz] = '\0';
        strcpy( dest, message );
}

void parseVentParamList( byte_buffer_t *bb) {
        log_debug(" parseVentParamList" );
        unsigned char num_params = bb_get(bb);
        unsigned char pad = bb_get(bb);

        for (int i = 0; i < num_params; i++) {
            unsigned char signal = bb_get(bb);
            unsigned char param_id = bb_get(bb);
            log_debug(" param: %d/%d = %s.%s", 
                        signal, param_id,
                        sig_gr_codes[signal], param_codes[param_id] );
        }
}
void parseVentCurrentMsg(byte_buffer_t *ndo_buffer) {
        log_debug(" parseVentCurrentMsg" );
}
void parseBedConfig(byte_buffer_t *ndo_buffer) {
        log_debug(" parseBedConfig" );
        char pat_pname[PATIENT_NAME_SIZE+1];
        char pat_initials[PATIENT_INITIALS_SIZE+1];
        char bed_label[BED_LABEL_SIZE+1];
           getFixedLengthString(pat_pname, ndo_buffer, PATIENT_NAME_SIZE);
        getFixedLengthString(pat_initials, ndo_buffer, PATIENT_INITIALS_SIZE);
        getFixedLengthString(bed_label, ndo_buffer, BED_LABEL_SIZE);
        int loc_control = bb_get_short(ndo_buffer);
        int rmt_control = bb_get_short(ndo_buffer);
        int barometric_pressure = bb_get_short(ndo_buffer);
        short pat_name_chars_plus_null = bb_get(ndo_buffer);
        short pat_initials_chars_plus_null = bb_get(ndo_buffer);
        short bed_label_chars_plus_null = bb_get(ndo_buffer);
        short freq_response = bb_get(ndo_buffer);
        short alarm_vol_percent = bb_get(ndo_buffer);
        short language = bb_get(ndo_buffer);
        short banners = bb_get(ndo_buffer);
        short pat_category = bb_get(ndo_buffer); // 1==ADULT
        short alarm_tones_mode = bb_get(ndo_buffer);
        short banners2 = bb_get(ndo_buffer);

        log_debug("  pname=%s  initials=%s  bed=%s", pat_pname, pat_initials, bed_label );
}

void parseDisplaySetup(byte_buffer_t *ndo_buffer) {
    short alarm_suspend_timeout = bb_get_short(ndo_buffer);
       unsigned char num_bands = bb_get(ndo_buffer);
    unsigned char num_pboxes = bb_get(ndo_buffer);
    unsigned char pbox1_pos = bb_get(ndo_buffer);
    unsigned char pbox_order = bb_get(ndo_buffer);
    horiz_pboxes = bb_get(ndo_buffer);
    unsigned char vert_pboxes = bb_get(ndo_buffer);
    unsigned char alarm_limit_display = bb_get(ndo_buffer);
    unsigned char pacer_detect = bb_get(ndo_buffer);
    unsigned char pacer_spike_display = bb_get(ndo_buffer);
    unsigned char resp_spike_display = bb_get(ndo_buffer);
    opmode = bb_get(ndo_buffer);
    unsigned char alarm_suspend = bb_get(ndo_buffer); // flag. mask 0x01 --> alarm
                                                // suspended
    unsigned char notes_counter = bb_get(ndo_buffer);
    unsigned char pboxIconDisplay = bb_get(ndo_buffer);

    bool changed;

    /*
    changed = (display.getPbox1Pos() != pbox1_pos);
    changed |= (display.getVertPboxes() != vert_pboxes);
    changed |= (display.getOpmode() != opmode);

    if (changed) {

            // display.setNumBands(num_bands);
            // display.setNumPboxes(num_pboxes);
            display.setPbox1Pos(pbox1_pos);
            display.setVertPboxes(vert_pboxes);
            display.setOpmode(opmode);

            // DONT CALL DISPLAY HERE...set a refresh request to --> true
            config_changed = true;
    }
    */

    // if (changed || alarm_suspend_timeout > 0) {

        // if (alarmsLog != NULL) {
            fprintf(stdout,"SETUP\t");
            fprintf(stdout,"OP:%d\t", opmode);
            fprintf(stdout,"BND:%d\t", num_bands);
            fprintf(stdout,"SUSP:%d\t", alarm_suspend);
            fprintf(stdout,"SUSTO:%d\t", alarm_suspend_timeout);
            fprintf(stdout,"PBOX:%d\t", num_pboxes);
            fprintf(stdout,"VERT:%d\t", vert_pboxes);
            fprintf(stdout,"POS:%d\t", pbox1_pos);
            fprintf(stdout,"\n");
        // }
    // }
}

void parseWaveform(byte_buffer_t *ndo_buffer) {
    short wvf = bb_get_short(ndo_buffer);
        char n_waves = bb_get(ndo_buffer);
        char channelId = bb_get(ndo_buffer);
        short dhdl = bb_get_short(ndo_buffer);
        short rnrd = bb_get_short(ndo_buffer);

        log_debug(" (waveform) %d channel=%d", wvf, channelId);

        bool reconfig = false;

        // ADDME: sensors.setTime(PlatformUtil.currentTimeMillis());

        int sig_count = 0;
        for (int i = 0; i < n_waves; i++) {

            int sampleRate = bb_get_short(ndo_buffer);
            int blockLen = bb_get_short(ndo_buffer);

            bb_get_int(ndo_buffer); // timestamp
            bb_get(ndo_buffer);
            bb_get(ndo_buffer); // part of timestamp
            int signalGroup = bb_get(ndo_buffer);
            int signalId = bb_get(ndo_buffer);

            int n_samples = bb_get(ndo_buffer);
            char spare = bb_get(ndo_buffer);

            void *desc = NULL; // findWaveformDescription(signalGroup, signalId);
            log_debug("  Waveform: %d/%d %s.%s", 
                            signalGroup, signalId, 
                            sig_gr_codes[ signalGroup], sig_id_codes[signalId] );
                // but we still need to parse the packet

            /* ADDME
            if (desc != NULL && !desc.isActive() && autoConfig) {
                reconfig = true;
                desc.setActive(true);
            }
            */

            if (desc != NULL) { /* ADDME && desc.isActive()) { */
                short *data = NULL; /* ADDME (int[]) IntfUtil.getRawValue(sensors, desc); */
                if (data == NULL ) { // ADDME || data.length != n_samples) {
                    log_warn("Allocating data for: %x", desc);
                    data = (short *)calloc( n_samples, 2 ); // new int[n_samples];
                    // ADDME IntfUtil.setValue(sensors, desc, data);
                }
                for (int j = 0; j < n_samples; j++) {
                    short point = bb_get_short(ndo_buffer);
                    data[j] = point / 4;
                }

                sig_count++;
            } else {
                // throw it away
                fprintf(stdout, "    ");
                for (int j = 0; j < n_samples; j++) {
                    short val = bb_get_short(ndo_buffer);
                    fprintf(stdout," %d", val );
                }
                fprintf(stdout,"\n");
            }

        }

        // if (autoConfig) { // is there anything in the config that is not in
        // the
        // // block?
        // reconfig = removeExtras(block, caps.getWaveformsRef());
        // }

        /* ADDME
        if (reconfig || send_initial_caps) {
            incrementDeviceName();
            fireCapabilitiesEvent(this, caps);
            send_initial_caps = false;
        }

        if (sig_count > 0) {
            fireStreamEvent(0, this, StreamID.WAVEFORM, sensors);
        }
        */

}

void parseWaveformSetup(byte_buffer_t *ndo_buffer) {
    log_info(" parseWaveformSetup");
}
void parseParameterAndAlarm(byte_buffer_t *ndo_buffer) {
    log_info(" parseParameterAndAlarm");
        unsigned char num_params = bb_get(ndo_buffer );
        unsigned char bytes_per_param = bb_get(ndo_buffer );

    	struct pista_data_packet *sendable = NULL;

        for (int i = 0; i < num_params; i++) {
            short param_val = bb_get_short(ndo_buffer );
            short param_upper_limit = bb_get_short(ndo_buffer );
            short param_lower_limit = bb_get_short(ndo_buffer );
            short alarm_limit = bb_get_short(ndo_buffer );
            getTimestamp(ndo_buffer); // paramTimestamp
            getTimestamp(ndo_buffer); // alarmTimestamp
            unsigned char signal_group = bb_get(ndo_buffer );
            unsigned char param_id = bb_get(ndo_buffer );
            unsigned char param_val_id = bb_get(ndo_buffer );
            unsigned char alarm_attrib = bb_get(ndo_buffer );
            unsigned char unit_of_measure = bb_get(ndo_buffer );
            unsigned char units_exp = bb_get(ndo_buffer );
            unsigned char show_units = bb_get(ndo_buffer );
            unsigned char alarm_condition = bb_get(ndo_buffer );
            unsigned char alarm_state = bb_get(ndo_buffer );
            unsigned char alarm_grade = bb_get(ndo_buffer );
            unsigned char curr_param_color = bb_get(ndo_buffer );
            unsigned char default_param_color = bb_get(ndo_buffer );
            unsigned char limits_type = bb_get(ndo_buffer );
            unsigned char background_color = bb_get(ndo_buffer );
            unsigned char is_flashing = bb_get(ndo_buffer );
            unsigned char num_decimals_to_display = bb_get(ndo_buffer );

            struct pista_item_desc *metric = findMetric(signal_group, param_id);

            /* ADDME
            if (metric == NULL) {
                String loc = getSignalGroup(signal_group) + "." + getParamCode(param_id);

                RpUnit u = new RpPrecisionUnit(-units_exp, NetUnitsOfMeasure.toText(unit_of_measure));
                metric = new RpMetric(loc, loc, null, u, DataTyp.INT_TYP);

                hm_mea.put(loc, metric);
            }
            */

#ifdef DEBUG
                        if (metric == NULL) {
                            log_debug("  %s.%s: ", sig_gr_codes[signal_group], param_codes[param_id]);
                        } else {
                            log_debug("  %s: ", metric->code);
                        }
                        log_debug("\tVAL:%d(%d)\tUL[%d,%d]\tALARM_LIMIT:%d ATTR:%d\tCOND:%d\tST:%d\tGR:%d", 
                                    param_val, num_decimals_to_display, 
                                    param_upper_limit, param_lower_limit,
                                    alarm_limit, alarm_attrib,
                                    alarm_condition, alarm_state, alarm_grade);

#endif  // DEBUG

            // ADDME    IntfUtil.setValue(measures, metric, param_val);
                
        }

        // TODO: 1- remove extra metrics
        // TODO: 2- indicate config/caps should be resent

        sendable->setTime(PlatformUtil.currentTimeMillis());
        if (EVERY_NTH > 1) {
            numeric_idx++;
            numeric_idx %= EVERY_NTH;
            if (numeric_idx == 0) {
                this.fireStreamEvent(0, this, StreamID.MEASUREMENT, sendable );
                clearNumerics();
            }
        } else {
            this.fireStreamEvent(0, this, StreamID.MEASUREMENT, sendable );
        }

        tick = 0;
}

void parseParameterBoxSetup(byte_buffer_t *ndo_buffer) {
    log_info(" parseParameterBoxSetup");
}
void parseCurrentMsgDisplayed(byte_buffer_t *ndo_buffer) {
    log_info(" parseCurrentMsgDisplayed");
}
void parseSummaryAlarmInfo(byte_buffer_t *ndo_buffer) {
    log_info(" parseSummaryAlarmInfo");

        //ADDME List<Alarm> currAlarms = new LinkedList<Alarm>();
        while (bb_bytes_left(ndo_buffer) > 0) {
            short alarm_limit = bb_get_short(ndo_buffer);
            getTimestamp(ndo_buffer); // alarmTimestamp
            char current_alarm_tone_grade = bb_get(ndo_buffer);
            char alarm_group_id = bb_get(ndo_buffer);
            char signal_group = bb_get(ndo_buffer);
            char param_id = bb_get(ndo_buffer);
            char alarm_condition = bb_get(ndo_buffer);
            char alarm_state = bb_get(ndo_buffer);
            char alarm_grade = bb_get(ndo_buffer);
            char is_flashing = bb_get(ndo_buffer);
            char foreground_color = bb_get(ndo_buffer);
            char background_color = bb_get(ndo_buffer);

            int cond = alarm_condition;
            if (cond < 0)
                cond += 256;

            char paramName[16]; 
            memset( paramName, 0, sizeof(paramName) );

            struct pista_item_desc *metric = findMetric(signal_group, param_id);
            if (metric == NULL) {
                sprintf(paramName, "%d/%d", signal_group, param_id);
            } else {
                strncpy(paramName, metric->code, sizeof(paramName) - 1 );
            }

            /* ADDME
            char pdc_code[16] = 0;

            if (cond < param_device_cond_codes.length) {
                pdc_code = param_device_cond_codes[cond];
            }
            if (pdc_code != NULL && pdc_code.equals("all alarms off")) {
                // ignore
            } else {
                Alarm ai = findAndRemoveAlarm(lastAlarms, cond, paramName);
                if (ai == NULL) {
                    ai = new Alarm(paramName, Alarm.WARNING, cond, paramName + ": " + pdc_code, true);
                    ai.setTm(new Date(now));
                    fireAlarmEvent(this, ai);
                    log_debug(" alarm on: {}", ai);
                }

                if (continuousAlarms == false) {
                    currAlarms.add(ai);
                }
                //ADDME if (alarmsLog != NULL) {
                    fprintf(stderr,"%d AL\t", addr);
                    fprintf(stderr,"%s\t", paramName);
                    fprintf(stderr,"%s\t", pdc_code);
                    fprintf(stderr,"%d\t", alarm_limit);
                    fprintf(stderr,"%d\t", alarm_condition);
                    fprintf(stderr,"%d\t", alarm_grade);
                    fprintf(stderr,"%d\t", alarm_group_id);
                    fprintf(stderr,"%d\n", current_alarm_tone_grade);
                //ADDME }

            }
            */

        /* ADDME
        if (continuousAlarms == false) {
            for (Alarm ai : lastAlarms) {
                ai.setActive(false);
                ai.setTm(new Date(now));
                ai.setMessage(ai.getMessage() + " / OFF");
                fireAlarmEvent(this, ai);

                log.debug(" alarm off: {}", ai);
            }
        }
        lastAlarms = currAlarms;
        */

    }
}

void parseVentWaveformDescription(byte_buffer_t *ndo_buffer) {
    log_info(" parseVentWaveformDescription");
}
void parseVentVolWaveformDescription(byte_buffer_t *ndo_buffer) {
    log_info(" parseVentVolWaveformDescription");
}
void parseSignalGroupIntervalMeasurement(byte_buffer_t *ndo_buffer, int len) { 
    log_info(" parseSignalGroupIntervalMeasurement");
}


void infinityNet_parsePacket( const uint8_t *data, size_t len ) {
    int opmode = 0;  // demo...
    int tick = 0;

    byte_buffer_t *bb = bb_new_wrap(data, len);
    uint16_t ndoId = bb_get_short(bb);
    uint16_t pad = bb_get_short(bb);
    int msgSeq = bb_get_int(bb);
    int julian = bb_get_int(bb);
    int deviceIp = bb_get_int(bb);

    bb_get_short(bb); // connect id

    bb_get_short(bb); // timestamp
    bb_get_int(bb);

    uint16_t majorVer = bb_get_short(bb);
    uint16_t minorVer = bb_get_short(bb);

    uint16_t n_bytes = bb_get(bb); // yes, byte in this context
    uint8_t n_ndo = bb_get(bb);
    uint16_t spare = bb_get_short(bb);


    for (int i = 0; i < n_ndo; i++) {
        ndoId = bb_get_short(bb);
        n_bytes = bb_get_short(bb);

        fprintf(stdout, "[%d,%d] ", ndoId, n_bytes );

        int pos = bb->pos;

        if (n_bytes == 0)
            break;

        byte_buffer_t *ndo_buffer = bb_new_wrap(&data[pos], n_bytes - 4);


        switch (ndoId) {
        case NDO_PDS_BED_CONFIG:
            if (opmode == 0)
                parseBedConfig(ndo_buffer);
            break;
        case NDO_PDS_DISPLAY_SETUP:
            tick = 0; // we call this connected, even if NO DATA is
                        // sent...standby
            parseDisplaySetup(ndo_buffer);
            break;
        case NDO_PDS_WAVEFORM:
            if (opmode == 0)
                parseWaveform(ndo_buffer);
            break;
        case NDO_PDS_WAVEFORM_SETUP:
            if (opmode == 0)
                parseWaveformSetup(ndo_buffer);
            break;
        case NDO_PDS_PARAMETER_AND_ALARM:
            if (opmode == 0)
                parseParameterAndAlarm(ndo_buffer);
            break;
        case NDO_PDS_PARAMETER_BOX_SETUP:
            if (opmode == 0)
                parseParameterBoxSetup(ndo_buffer);
            break;
        case NDO_PDS_CURRENT_MSG_DISPLAYED:
            if (opmode == 0)
                parseCurrentMsgDisplayed(ndo_buffer);
            break;
        case NDO_PDS_SUMMARY_ALARM_INFO:
            if (opmode == 0)
                parseSummaryAlarmInfo(ndo_buffer);
            break;

        case NDO_PDS_VENT_CURRENT_MSG:
            if (opmode == 0)
                parseVentCurrentMsg(ndo_buffer);
            break;

        case NDO_PDS_VENT_WV_DESC:
            if (opmode == 0)
                parseVentWaveformDescription(ndo_buffer);
            break;

        case NDO_PDS_VENT_PARAM_LIST:
            if (opmode == 0)
            parseVentParamList(ndo_buffer);
            break;

        case NDO_PDS_VENT_VOL_WV_DESC:
            if (opmode == 0)
                parseVentVolWaveformDescription(ndo_buffer);
            break;

        case UNKNOWN_NDO_PDS_28:
            // intentionally ignoring this value...occurs!
            log_info(" UNKNOWN_NDO_PDS_28 unknown ndoId");
            break;
        case UNKNOWN_NDO_34:
            // intentionally ignoring this value...occurs!
            log_info(" UNKNOWN_NDO_34 unknown ndoId");
            break;
        case NDO_PDS_SIGNAL_GROUP_INTERVAL_MEASUREMENT:
            if (opmode == 0)
                parseSignalGroupIntervalMeasurement(ndo_buffer, n_bytes - 4);
            break;
        default:
            log_warn(" unknown ndoId: %d", ndoId);

        }
        bb_free(ndo_buffer);
        bb->pos = pos + n_bytes - 4;
    }
    bb_free(bb);

}

