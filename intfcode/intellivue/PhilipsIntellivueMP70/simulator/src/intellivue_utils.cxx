/**
 * @file intellivue_utils.cxx
 *
 * Reference:
 * 	Data Export Interface Programming Guide
 * 	IntelliVue Patient Monitor
 * 	MP70
 *
 * 	Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================

#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <string.h>
#include "intellivue_utils.h"

#ifndef _WIN32

int16_t bytes216(uint8_t* bytes)
{
	int16_t shortval = *((int16_t*)bytes);
	return((int16_t)ntohs(shortval));
}

uint16_t bytes2u16(uint8_t* bytes)
{
	uint16_t shortval = *((uint16_t*)bytes);
	return(ntohs(shortval));
}

uint32_t bytes2u32(uint8_t* bytes)
{
	uint32_t intval = *((uint32_t*)bytes);
	return(ntohl(intval));
}

#endif

void int22bytes(uint8_t* rbuf, int sx)
{
	short newsx = htons(sx);
	uint8_t* pnew = (uint8_t*)&newsx;
	memcpy(rbuf, pnew, sizeof(newsx));
	uint8_t* prbuf = rbuf;
}

void int24bytes(uint8_t* rbuf, int lx)
{
	int newlx = htonl(lx);
	uint8_t* pnew = (uint8_t*)&newlx;
	memcpy(rbuf, pnew, sizeof(lx));
	uint8_t* prbuf = rbuf;
}

int merge(uint8_t* pdest, uint8_t* arrA, size_t sa, uint8_t* arrB, size_t sb)
{
  if (!pdest)
  {
    return __LINE__;
  }

  // Copy elements from A into C
  memcpy(&pdest[0], arrA, sa);

  // Copy elements from B into C, starting at the end of A elements
  memcpy(&pdest[sa], arrB, sb);

  return 0;
}

#if 0

char g_smd_ipaddr[32];

static int SaSpec_counter = 0;
static int ScaleSpec_counter = 0;

vector<SavedSAattr> gSavedSAattr;
SavedSAattr ssa = {0};

static int Numeric_cmpd_count = 1;

/**
 * Store attribute contents into the dds transport object.
 * @param [in] buf buffer containing response bytes from intellivue monitor.
 * @param [in] iindex current index in the byte buffer.
 * @param [in] attrib_id parsed attribute id.
 * @param [in] attrib_len length of attribute contents in bytes.
 * @param [in, out] dbx_mds pointer to dds structure being transported
 * @return attribute containing id and pointer to structure.
 */
dbx_attrib store_attribute_entry( uint8_t* buf, int iindex, int attrib_id, int attrib_len)
{
	dbx_attrib dbxa = {0};

	switch(attrib_id)
	{
		case NOM_ATTR_AL_MON_P_AL_LIST:
		{
			dbxa.id = NOM_ATTR_AL_MON_P_AL_LIST;
			size_t size = (size_t)0;
			DevAlarmList_intellivue* pdal = 0;
			DevAlarmEntry_intellivue value = {0};
			DevAlarmList_intellivue dal = {0};

			dal.count = bytes2u16(&buf[iindex]);
			dal.length = bytes2u16(&buf[iindex + 2]);

			// Storing results in transport structure for DDS.
			/* TODO dbx_mds->pollReply.alert_monitor.device_p_alarm_list.count = dal.count;
			dbx_mds->pollReply.alert_monitor.device_p_alarm_list.length = dal.length;
*/
			if(dal.count == 0)
				dbxa.ps = new uint8_t[sizeof(DevAlarmList_intellivue)];
			else
				dbxa.ps = new uint8_t[sizeof(DevAlarmList_intellivue) + (sizeof(DevAlarmEntry_intellivue) * (dal.count - 1))];

			pdal = reinterpret_cast<DevAlarmList_intellivue*>(dbxa.ps);
			*pdal = dal;

			iindex += 4;
			for(int ix = 0; ix < pdal->count; ix++)
			{
				value.al_source = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_code = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_type = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_state = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.object.m_obj_class = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.object.m_obj_inst.context_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				pdal->value[ix].object.m_obj_inst.handle = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.alert_info_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.length = bytes2u16(&buf[iindex]);
				iindex += 2;
				pdal->value[ix] = value;

				/* TODO dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].al_source = value.al_source;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].al_code = value.al_code;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].al_type = value.al_type;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].al_state = value.al_state;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].object.m_obj_class = value.object.m_obj_class;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].object.m_obj_inst.context_id = value.object.m_obj_inst.context_id;
				dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].alert_info_id = value.alert_info_id;
*/
				if(value.alert_info_id == GEN_ALMON_INFO)
				{
					AlMonGenInfo gen = {0};
					AlMonGenInfo* pgen = 0;

					pdal->value[ix].ps = new uint8_t[sizeof(AlMonGenInfo)];
					pgen = reinterpret_cast<AlMonGenInfo *>(pdal->value[ix].ps);
					*pgen = gen;

					pgen->al_inst_no = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->al_text = bytes2u32(&buf[iindex]);
					iindex += 4;
					pgen->priority = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->flags = bytes2u16(&buf[iindex]);

					/* TODO memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string, &(pgen->al_inst_no), sizeof(pgen->al_inst_no));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no), &(pgen->al_text), sizeof(pgen->al_text));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text), &(pgen->priority), sizeof(pgen->priority));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority), &(pgen->flags), sizeof(pgen->flags));
					*/size = sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority) + sizeof(pgen->flags);
				}

				if(value.alert_info_id == STR_ALMON_INFO)
				{
					StrAlMonInfo gen = {0};
					StrAlMonInfo* pgen = 0;

					pdal->value[ix].ps = new uint8_t[sizeof(StrAlMonInfo) + (sizeof(uint8_t) * bytes2u16(&buf[iindex + 10]))];
					pgen = reinterpret_cast<StrAlMonInfo *>(pdal->value[ix].ps);
					*pgen = gen;

					pgen->al_inst_no = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->al_text = bytes2u32(&buf[iindex]);
					iindex += 4;
					pgen->priority = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->flags = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->string.length = bytes2u16(&buf[iindex]);
					iindex += 2;

					/* TODO memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string, &(pgen->al_inst_no), sizeof(pgen->al_inst_no));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no), &(pgen->al_text), sizeof(pgen->al_text));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text), &(pgen->priority), sizeof(pgen->priority));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority), &(pgen->flags), sizeof(pgen->flags));
					*/size = sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority) + sizeof(pgen->flags);

					for(int iy = 0; iy < pgen->string.length / 2; iy++)
					{
						pgen->string.value[iy] = bytes2u16(&buf[iindex]);
						iindex += 2;
						/* TODO memcpy((void*)dbx_mds->pollReply.alert_monitor.device_p_alarm_list.value[ix].almon_string + size, &(pgen->string.value[iy]), sizeof(pgen->string.value[iy]));
					*/
					}
				}
			}
		}
		break;

		case NOM_ATTR_AL_MON_T_AL_LIST:
		{
			dbxa.id = NOM_ATTR_AL_MON_T_AL_LIST;
			DevAlarmList_intellivue* pdal = 0;
			DevAlarmEntry_intellivue value = {0};
			size_t size = (size_t)0;
			DevAlarmList_intellivue dal =
			{
				bytes2u16(&buf[iindex]),
				bytes2u16(&buf[iindex + 2]),
				{0}
			};

			/* TODO dbx_mds->pollReply.alert_monitor.device_t_alarm_list.count = dal.count;
			dbx_mds->pollReply.alert_monitor.device_t_alarm_list.length = dal.length;
*/
			if(dal.count == 0)
				dbxa.ps = new uint8_t[sizeof(DevAlarmList_intellivue)];
			else
				dbxa.ps = new uint8_t[sizeof(DevAlarmList_intellivue) + 500];

			pdal = reinterpret_cast<DevAlarmList_intellivue *>(dbxa.ps);
			*pdal = dal;

			iindex += 4;

			for(int ix = 0; ix < dal.count; ix++)
			{
				value.al_source = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_code = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_type = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.al_state = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.object.m_obj_class = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.object.m_obj_inst.context_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.object.m_obj_inst.handle = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.alert_info_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.length = bytes2u16(&buf[iindex]);
				iindex += 2;
				pdal->value[ix] = value;

				/* TODO dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].al_source = value.al_source;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].al_code = value.al_code;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].al_type = value.al_type;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].al_state = value.al_state;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].object.m_obj_class = value.object.m_obj_class;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].object.m_obj_inst.context_id = value.object.m_obj_inst.context_id;
				dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].alert_info_id = value.alert_info_id;
*/
				if(value.alert_info_id == GEN_ALMON_INFO)
				{
					AlMonGenInfo gen = {0};
					AlMonGenInfo* pgen = 0;

					pdal->value[ix].ps = new uint8_t[sizeof(AlMonGenInfo)];
					pgen = reinterpret_cast<AlMonGenInfo *>(pdal->value[ix].ps);
					*pgen = gen;

					pgen->al_inst_no = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->al_text = bytes2u32(&buf[iindex]);
					iindex += 4;
					pgen->priority = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->flags = bytes2u16(&buf[iindex]);

					/* TODO memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string, &(pgen->al_inst_no), sizeof(pgen->al_inst_no));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no), &(pgen->al_text), sizeof(pgen->al_text));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text), &(pgen->priority), sizeof(pgen->priority));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority), &(pgen->flags), sizeof(pgen->flags));
				*/	size = sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority) + sizeof(pgen->flags);
				}

				if(value.alert_info_id == STR_ALMON_INFO)
				{
					StrAlMonInfo gen = {0};
					StrAlMonInfo* pgen = 0;

					pdal->value[ix].ps = new uint8_t[sizeof(StrAlMonInfo) + (sizeof(uint8_t) * bytes2u16(&buf[iindex + 10]))];
					pgen = reinterpret_cast<StrAlMonInfo *>(pdal->value[ix].ps);
					*pgen = gen;

					pgen->al_inst_no = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->al_text = bytes2u32(&buf[iindex]);
					iindex += 4;
					pgen->priority = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->flags = bytes2u16(&buf[iindex]);
					iindex += 2;
					pgen->string.length = bytes2u16(&buf[iindex]);
					iindex += 2;

					/* TODO memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string, &(pgen->al_inst_no), sizeof(pgen->al_inst_no));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no), &(pgen->al_text), sizeof(pgen->al_text));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text), &(pgen->priority), sizeof(pgen->priority));
					memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority), &(pgen->flags), sizeof(pgen->flags));
					*/size = sizeof(pgen->al_inst_no) + sizeof(pgen->al_text) + sizeof(pgen->priority) + sizeof(pgen->flags);

					for(int iy = 0; iy < pgen->string.length / 2; iy++)
					{
						pgen->string.value[iy] = bytes2u16(&buf[iindex]);
						iindex += 2;

						/*if(size < MAXSTRSIZE_DEV_ALMON_ENTRY){}
						   TODO 	memcpy((void*)dbx_mds->pollReply.alert_monitor.device_t_alarm_list.value[ix].almon_string + size, &(pgen->string.value[iy]), sizeof(pgen->string.value[iy]));
						*/size += sizeof(pgen->string.value[iy]);
					}
				}
			}
		}
		break;

		case NOM_ATTR_ALTITUDE:
		{
			dbxa.id = NOM_ATTR_ALTITUDE;
			uint16_t* pdal = 0;
			uint16_t altitude = 0;
			int isize = 0;

			altitude = bytes216(&buf[iindex]);
			isize = sizeof(uint16_t);
			dbxa.ps = new uint8_t [isize];
			pdal = reinterpret_cast<uint16_t* >(dbxa.ps);
			*pdal = altitude;

			/* TODO dbx_mds->pollReply.mds.Altitude = altitude;*/
		}
		break;

		case NOM_ATTR_AREA_APPL:
		{
			dbxa.id = NOM_ATTR_AREA_APPL;
			uint16_t* pdal = 0;
			ApplicationArea aa = {0};
			int isize = 0;

			aa = bytes2u16(&buf[iindex]);
			isize = sizeof(ApplicationArea);
			dbxa.ps = new uint8_t [isize];
			pdal = reinterpret_cast<ApplicationArea *>(dbxa.ps);
			*pdal = aa;

			/* TODO dbx_mds->pollReply.mds.Application_area = aa;*/
		}
		break;

		case NOM_ATTR_COLOR:
		{
			dbxa.id = NOM_ATTR_COLOR;
			uint16_t* pdal = 0;
			SimpleColour sc = {0};

			sc = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t [sizeof(SimpleColour)];
			pdal = reinterpret_cast<SimpleColour *>(dbxa.ps);
			*pdal = sc;
		}
		break;

		case NOM_ATTR_DEV_AL_COND:
		{
			int size = 0;
			DeviceAlertCondition *pdac = 0;
			DeviceAlertCondition dac = {0};

			dbxa.id = NOM_ATTR_DEV_AL_COND;
			dac.device_alert_state = bytes2u16(&buf[iindex]);
			iindex += 2;
			dac.al_stat_chg_cnt = bytes2u16(&buf[iindex]);
			iindex += 2;
			dac.max_p_alarm = bytes2u16(&buf[iindex]);
			iindex += 2;
			dac.max_t_alarm = bytes2u16(&buf[iindex]);
			iindex += 2;
			dac.max_aud_alarm = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(DeviceAlertCondition);
			dbxa.ps = new uint8_t[size];
			pdac = reinterpret_cast<DeviceAlertCondition *>(dbxa.ps);
			*pdac = dac;

			/* TODO dbx_mds->pollReply.alert_monitor.dev_alert_condition.device_alert_state = dac.device_alert_state;
			dbx_mds->pollReply.alert_monitor.dev_alert_condition.al_stat_chg_cnt = dac.al_stat_chg_cnt;
			dbx_mds->pollReply.alert_monitor.dev_alert_condition.max_p_alarm = dac.max_p_alarm;
			dbx_mds->pollReply.alert_monitor.dev_alert_condition.max_t_alarm = dac.max_t_alarm;
			dbx_mds->pollReply.alert_monitor.dev_alert_condition.max_aud_alarm = dac.max_aud_alarm;*/
		}
		break;

		case NOM_ATTR_DISP_RES:
		{
			dbxa.id = NOM_ATTR_DISP_RES;
			DispResolution_intellivue* pdr = 0;
			DispResolution_intellivue dr = {0};
			int size = 0;

			dr.pre_point = buf[iindex];
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].disp_res.pre_point = dr.pre_point;*/
			iindex += 2;

			dr.post_point = buf[iindex];
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].disp_res.post_point = dr.post_point;*/

			size = sizeof(DispResolution_intellivue);
			dbxa.ps = new uint8_t[size];
			pdr = reinterpret_cast<DispResolution_intellivue *>(dbxa.ps);
			*pdr = dr;
		}
		break;

		case NOM_ATTR_GRID_VIS_I16:
		{
			dbxa.id = NOM_ATTR_GRID_VIS_I16;
			SaVisualGrid16 *psvg = 0;
			SaVisualGrid16 svg = {0};
			int size = 0;

			svg.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			svg.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(SaVisualGrid16) + sizeof(SaGridEntry16) * (svg.count -1);
			dbxa.ps = new uint8_t[size];
			psvg = reinterpret_cast<SaVisualGrid16 *> (dbxa.ps);
			*psvg = svg;

			for(int ix = 0; ix < svg.count; ix++)
			{
				SaGridEntry16 value = {0};
				int8_t exponent = 0;
				int mantissa = 0;

				exponent = (int8_t)buf[iindex];
				mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
				value.absolute_value = mantissa | (exponent << 24);

				iindex += 4;
				value.scaled_value = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.level = bytes2u16(&buf[iindex]);
				iindex += 2;

				psvg->value[ix] = value;
			}
		}
		break;

		case NOM_ATTR_ID_ASSOC_NO:
		{
			dbxa.id = NOM_ATTR_ID_ASSOC_NO;
			uint16_t* pd = 0;
			uint16_t id = 0;

			id = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(uint16_t)];
			pd = reinterpret_cast<uint16_t *> (dbxa.ps);
			*pd = id;
		}
		break;

		case NOM_ATTR_ID_BED_LABEL:
		{
			dbxa.id = NOM_ATTR_ID_BED_LABEL;
			String* ps = 0;
			String sstr = {0};
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;

			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
				/* TODO if(ix < MAXSTRSIZE_LABEL)
				{
				  	dbx_mds->pollReply.mds.Bed_Label[ix] = value;
				}*/
			}
		}
		break;

		case NOM_ATTR_ID_HANDLE:
		{
			dbxa.id = NOM_ATTR_ID_HANDLE;
			Handle* phandle = 0;
			Handle handle = 0;

			handle = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(Handle)];
			phandle = reinterpret_cast<Handle *>(dbxa.ps);
			*phandle = handle;

			/* TODO 	dbx_mds->pollReply.vms.Handle = handle;
			dbx_mds->pollReply.alert_monitor.vmo.Handle = handle;
			dbx_mds->pollReply.pat_demog.Handle = handle;*/
		}
		break;

		case NOM_ATTR_ID_LABEL:
		{
			dbxa.id = NOM_ATTR_ID_LABEL;
			TextId* ptid = 0;
			TextId tid = {0};

			tid = bytes2u32(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(TextId)];
			ptid = reinterpret_cast<TextId *>(dbxa.ps);
			*ptid = tid;
		}
		break;

		case NOM_ATTR_ID_LABEL_STRING:
		{
			dbxa.id = NOM_ATTR_ID_LABEL_STRING;
			String* ps = 0;
			String s = {0};
			int size = 0;

			s.length = bytes2u16(&buf[iindex]);
			iindex += 2;
			size = sizeof(String) + sizeof(uint16_t) * (s.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = s;

			for(int i = 0; i < s.length; i++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[i] = value;
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].label_string[i] = buf[iindex];*/
			}
		}
		break;

		case NOM_ATTR_ID_MODEL:
		{
			dbxa.id = NOM_ATTR_ID_MODEL;
			SystemModel_intellivue* ps = 0;
			SystemModel_intellivue sm = {0};
			VariableLabel* manufacturer = 0;
			VariableLabel* model_number = 0;

			dbxa.ps = new uint8_t[sizeof(SystemModel_intellivue)];
			ps = reinterpret_cast<SystemModel_intellivue *>(dbxa.ps);

			// Manufacturer
			// Allocate space for manufacturer
			sm.manufacturer = new uint8_t[sizeof(uint8_t) * (bytes2u16(&buf[iindex + 2]))];
			manufacturer = reinterpret_cast<VariableLabel *> (sm.manufacturer);

			manufacturer->length = bytes2u16(&buf[iindex]);
			iindex += 2;

			// Store chars in value array of manufacturer.
			for (int iy = 0; iy < manufacturer->length; iy++)
			{
				manufacturer->value[iy] = buf[iindex + iy];
				/* TODO if(iy < MAXSTRSIZE_LABEL)
				dbx_mds->pollReply.vms.System_Model.manufacturer[iy] = manufacturer->value[iy];*/
			}
			iindex += manufacturer->length;

			// Model number
			// Do the same for model number
			sm.model_number = new uint8_t[sizeof(uint8_t) * (bytes2u16(&buf[iindex + 2]))];
			model_number = reinterpret_cast<VariableLabel *> (sm.model_number);

			model_number->length = bytes2u16(&buf[iindex]);
			iindex += 2;

			// Get characters from buffer.
			for (int iy = 0; iy < model_number->length; iy++)
			{
				model_number->value[iy] = buf[iindex + iy];
				/* TODO   if(iy < MAXSTRSIZE_LABEL)
				dbx_mds->pollReply.vms.System_Model.model_number[iy] = model_number->value[iy];*/
			}
			iindex += model_number->length;

			*ps = sm;
		}
		break;

		case NOM_ATTR_ID_PROD_SPECN:
		{
			dbxa.id = NOM_ATTR_ID_PROD_SPECN;
			ProductionSpec_intellivue pspec =
			{
				bytes2u16(&buf[iindex]),
				bytes2u16(&buf[iindex + 2]),
				{0}
			};
			ProductionSpec_intellivue* ps = 0;

			iindex += 4;

			dbxa.ps = new uint8_t[(sizeof(uint8_t) * (pspec.length + 4))];
			ps = reinterpret_cast<ProductionSpec_intellivue *> (dbxa.ps);
			*ps = pspec;

			/* TODO dbx_mds->pollReply.vms.Production_Specification.count = pspec.count;*/
			for (int ix = 0; ix < pspec.count; ix++)
			{
				ProdSpecEntry_intellivue value = {0};
				VariableLabel* vl = 0;

				value.spec_type = bytes2u16(&buf[iindex]);
				value.component_id = bytes2u16(&buf[iindex + 2]);

				value.prod_spec = new uint8_t[(bytes2u16(&buf[iindex + 4]) + 2) * sizeof(uint8_t)];
				vl = reinterpret_cast<VariableLabel *>(value.prod_spec);
				vl->length = bytes2u16(&buf[iindex + 4]);
				iindex += 6;

				ps->value[ix] = value;
				/* TODO if(ix < MAX_PRODSPECENTRIES)
				{
				  dbx_mds->pollReply.vms.Production_Specification.value[ix].spec_type = value.spec_type;
					dbx_mds->pollReply.vms.Production_Specification.value[ix].component_id = value.component_id;
				}
*/
				for (int iy = 0; iy < vl->length; iy++)
				{
					char ch = '\0';
					ch = buf[iindex + iy];
					vl->value[iy] = ch;

					/* TODOif(ix < MAX_PRODSPECENTRIES)
					{
						if(iy < MAXSTRSIZE_LABEL){}
						 dbx_mds->pollReply.vms.Production_Specification.value[ix].prod_spec[iy] = vl->value[iy];
					}*/
				}
				iindex += vl->length;
			}
		}
		break;

		case NOM_ATTR_ID_TYPE:
		{
			dbxa.id = NOM_ATTR_ID_TYPE;
			TYPE t = {0};
			TYPE* pt = 0;

			dbxa.ps = new uint8_t[sizeof(TYPE)];
			pt = reinterpret_cast<TYPE *> (dbxa.ps);

			t.partition = bytes2u16(&buf[iindex]);
			t.code = bytes2u16(&buf[iindex + 2]);
			*pt = t;

			/* TODO dbx_mds->pollReply.alert_monitor.vmo.type.partition = t.partition;
			dbx_mds->pollReply.alert_monitor.vmo.type.code = t.code;*/
		}
		break;

		case NOM_ATTR_LINE_FREQ:
		{
			dbxa.id = NOM_ATTR_LINE_FREQ;
			LineFrequency lf = bytes2u16(&buf[iindex]);
			LineFrequency* plf = 0;

			dbxa.ps = new uint8_t[sizeof(LineFrequency)];
			plf = reinterpret_cast<LineFrequency *>(dbxa.ps);
			*plf = lf;

			/* TODO 	dbx_mds->pollReply.mds.Line_Frequency = lf;*/
		}
		break;

		case NOM_ATTR_LOCALIZN:
		{
			dbxa.id = NOM_ATTR_LOCALIZN;
			SystemLocal tsl =
			{
				bytes2u32(&buf[iindex]),	// text_catalog_revision
				bytes2u16(&buf[iindex + 4]),	// language
				bytes2u16(&buf[iindex + 6]),	// format
			};
			SystemLocal* sl = 0;

			dbxa.ps = new uint8_t[sizeof(SystemLocal)];
			sl = reinterpret_cast<SystemLocal *>(dbxa.ps);
			*sl = tsl;
		}
		break;

		case NOM_ATTR_METRIC_INFO_LABEL:
		{
			dbxa.id = NOM_ATTR_METRIC_INFO_LABEL;
			TextId tid = {0};
			TextId* ptid = 0;

			tid = bytes2u32(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(TextId)];
			ptid = reinterpret_cast<TextId *>(dbxa.ps);
			*ptid = tid;
		}
		break;

		case NOM_ATTR_METRIC_INFO_LABEL_STR:
		{
			dbxa.id = NOM_ATTR_METRIC_INFO_LABEL_STR;
			String str = {0};
			String* ps = 0;
			int size = 0;

			str.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(String) + sizeof(uint16_t) * (str.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = str;
			for(int ix = 0; ix < str.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
			}
		}
		break;

		case NOM_ATTR_METRIC_SPECN:
		{
			dbxa.id = NOM_ATTR_METRIC_SPECN;
			/* TODOMetricSpec_intellivue ms = {0};
			MetricSpec* pms = 0;

			ms.update_period = bytes2u32(&buf[iindex]);
			 dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.update_period = ms.update_period;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.update_period = ms.update_period;
			ssa.metricspec.update_period = ms.update_period;
			iindex += 4;
			ms.category = bytes2u16(&buf[iindex]);
			TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.category = ms.category;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.category = ms.category;
			ssa.metricspec.category = ms.category;
			iindex += 2;
			ms.access = bytes2u16(&buf[iindex]);
		TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.access = ms.access;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.access = ms.access;
			ssa.metricspec.access = ms.access;
			iindex += 2;
			ms.structure.ms_struct = buf[iindex];
			 TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.structure.ms_struct = ms.structure.ms_struct;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.structure.ms_struct = ms.structure.ms_struct;
			ssa.metricspec.structure.ms_struct = ms.structure.ms_struct;
			iindex += 1;
			ms.structure.ms_comp_no = buf[iindex];
			TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.structure.ms_comp_no = ms.structure.ms_comp_no;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.structure.ms_comp_no = ms.structure.ms_comp_no;
			ssa.metricspec.structure.ms_comp_no = ms.structure.ms_comp_no;
			iindex += 1;
			ms.relevance = bytes2u16(&buf[iindex]);
			TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.relevance = ms.relevance;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metricspec.relevance = ms.relevance;
			ssa.metricspec.relevance = ms.relevance;

			dbxa.ps = new uint8_t[sizeof(MetricSpec)];
			pms = reinterpret_cast<MetricSpec *> (dbxa.ps);
			*pms = ms;*/
		}
		break;

		case NOM_ATTR_METRIC_STAT:
		{
			dbxa.id = NOM_ATTR_METRIC_STAT;
			MetricState* pms = 0;
			MetricState ms = {0};

			ms = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(MetricState)];
			pms = reinterpret_cast<MetricState *>(dbxa.ps);
			*pms = ms;
		}
		break;

		case NOM_ATTR_MODE_MSMT:
		{
			dbxa.id = NOM_ATTR_MODE_MSMT;
			MeasureMode* pmm = 0;
			MeasureMode mm = {0};

			mm = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(MeasureMode)];
			pmm = reinterpret_cast<MeasureMode *>(dbxa.ps);
			*pmm = mm;
		}
		break;

		case NOM_ATTR_MODE_OP:
		{
			dbxa.id = NOM_ATTR_MODE_OP;
			PrivateOID* ppoid = 0;
			PrivateOID poid = {0};

			poid = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PrivateOID)];
			ppoid = reinterpret_cast<PrivateOID *>(dbxa.ps);
			*ppoid = poid;

			/* TODO dbx_mds->pollReply.mds.Operating_mode = poid;*/
		}
		break;

		case NOM_ATTR_NOM_VERS:
		{
			dbxa.id = NOM_ATTR_NOM_VERS;
			uint32_t* pu32 = 0;
			uint32_t u32 = 0;
			uint8_t Fval[4] = {0};
			uint32_t major = 0;
			uint32_t minor = 0;

			u32 = bytes2u32(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(uint32_t)];
			pu32 = reinterpret_cast<uint32_t *>(dbxa.ps);
			*pu32 = u32;

			int24bytes(&Fval[0], u32);
			major = bytes2u16(&Fval[0]);
			minor = bytes2u16(&Fval[2]);

			/* TODO dbx_mds->pollReply.vms.Nomenclature_version.nom_major_version = major;
			dbx_mds->pollReply.vms.Nomenclature_version.nom_minor_version = minor;*/
		}
		break;

		case NOM_ATTR_NU_CMPD_VAL_OBS:
		{
			dbxa.id = NOM_ATTR_NU_CMPD_VAL_OBS;
			NuObsValueCmp_intellivue* pnucmp = 0;
			NuObsValueCmp_intellivue nucmp = {0};

			nucmp.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			nucmp.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(NuObsValueCmp_intellivue)+ (nucmp.count - 1) * sizeof(NuObsValue_intellivue)];
			pnucmp = reinterpret_cast<NuObsValueCmp_intellivue *>(dbxa.ps);
			*pnucmp = nucmp;
			Numeric_cmpd_count =  nucmp.count;
			for(int jx = 1; jx < nucmp.count; jx++)
			{
			  /* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.update_period = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.update_period;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.category = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.category;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.access = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.access;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.structure.ms_struct = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.structure.ms_struct;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.structure.ms_comp_no = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.structure.ms_comp_no;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].metricspec.relevance = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metricspec.relevance;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].disp_res.pre_point = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].disp_res.pre_point;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].disp_res.post_point = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].disp_res.post_point;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].rel_time = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].rel_time;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.century = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.century;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.year = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.year;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.month = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.month;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.day = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.day;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.hour = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.hour;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.minute = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.minute;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.second = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.second;
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].abs_time.sec_fractions = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.sec_fractions;
				for(int kx = 0; kx < MAXSTRSIZE_LABEL; kx++)
				dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count + jx].label_string[kx] = dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].label_string[kx];
			*/}

			for(int ix = 0; ix < nucmp.count; ix++)
			{
				NuObsValue_intellivue value = {0};
				value.physio_id = bytes2u16(&buf[iindex]);
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metric_id = value.physio_id;*/
				iindex += 2;
				value.state = bytes2u16(&buf[iindex]);
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].state = value.state;*/
				iindex += 2;
				value.unit_code = bytes2u16(&buf[iindex]);
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].unit_code = value.unit_code;*/
				iindex += 2;
				value.value = bytes2u32(&buf[iindex]);
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].value = value.value;*/
				iindex += 4;

				pnucmp->value[ix] = value;
				/* TODO dbx_mds->pollReplyExt.nu_val_cmp.count++;*/
			}
		}
		break;

		case NOM_ATTR_NU_VAL_OBS:
		{
			dbxa.id = NOM_ATTR_NU_VAL_OBS;
			NuObsValue_intellivue* pnov = 0;
			NuObsValue_intellivue nov = {0};
			Numeric_cmpd_count = 1;

			nov.physio_id = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].metric_id = nov.physio_id;*/
			iindex += 2;
			nov.state = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].state = nov.state;*/
			iindex += 2;
			nov.unit_code = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].unit_code = nov.unit_code;*/
			iindex += 2;
			nov.value = bytes2u32(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].value = nov.value;*/
			iindex += 4;

			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.count++;*/

			dbxa.ps = new uint8_t[sizeof(NuObsValue_intellivue)];
			pnov = reinterpret_cast<NuObsValue_intellivue *>(dbxa.ps);
			*pnov = nov;
		}
		break;

		case NOM_ATTR_PT_BSA:
		{
		  dbxa.id = NOM_ATTR_PT_BSA;
		  /* TODO PatMeasure* ppm = 0;
			PatMeasure pm = {0};
			uint8_t exponent = 0;
			int mantissa = 0;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			pm.value = mantissa | (exponent << 24);

			iindex += 4;
			pm.m_unit = bytes2u16(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(PatMeasure)];
			ppm = reinterpret_cast<PatMeasure *>(dbxa.ps);
			*ppm = pm;

			dbx_mds->pollReply.pat_demog.patient_bsa.value = pm.value;
			dbx_mds->pollReply.pat_demog.patient_bsa.m_unit = pm.m_unit;*/
		}
		break;

		case NOM_ATTR_PT_DEMOG_ST:
		{
			dbxa.id = NOM_ATTR_PT_DEMOG_ST;
			PatDmgState *ppds = 0;
			PatDmgState pds = {0};

			pds = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatDmgState)];
			ppds = reinterpret_cast<PatDmgState *>(dbxa.ps);
			*ppds = pds;

			/* TODO dbx_mds->pollReply.pat_demog.pat_demo_state = pds;*/
		}
		break;

		case NOM_ATTR_PT_DOB:
		{
			dbxa.id = NOM_ATTR_PT_DOB;
			AbsoluteTime_intellivue* pdob = 0;
			AbsoluteTime_intellivue dob = {0};

			dob.century = (uint8_t)buf[iindex];
			dob.year = (uint8_t)buf[iindex + 1];
			dob.month = (uint8_t)buf[iindex + 2];
			dob.day = (uint8_t)buf[iindex + 3];
			dob.hour = (uint8_t)buf[iindex + 4];
			dob.minute = (uint8_t)buf[iindex + 5];
			dob.second = (uint8_t)buf[iindex + 6];
			dob.sec_fractions = (uint8_t)buf[iindex + 7];

			dbxa.ps = new uint8_t[sizeof(AbsoluteTime_intellivue)];
			pdob = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			*pdob = dob;

			/* TODO dbx_mds->pollReply.pat_demog.date_of_birth.century = dob.century;
			dbx_mds->pollReply.pat_demog.date_of_birth.year = dob.year;
			dbx_mds->pollReply.pat_demog.date_of_birth.month = dob.month;
			dbx_mds->pollReply.pat_demog.date_of_birth.day = dob.day;*/
		}
		break;

		case NOM_ATTR_PT_ID:
		{
			dbxa.id = NOM_ATTR_PT_ID;
			String sstr = {0};
			String* ps = 0;
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;
			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;
			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
				/* TODO if(ix < MAXSTRSIZE_LABEL)
					dbx_mds->pollReply.pat_demog.patient_id[ix] = value;*/
			}
		}
		break;

		case NOM_ATTR_PT_NAME_FAMILY:
		{
			dbxa.id = NOM_ATTR_PT_NAME_FAMILY;
			String sstr = {0};
			String* ps = 0;
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;
			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;
			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
				/* TODO if(ix < MAXSTRSIZE_LABEL)
				dbx_mds->pollReply.pat_demog.family_name[ix] = value;*/
			}
		}
		break;

		case NOM_ATTR_PT_NAME_GIVEN:
		{
			dbxa.id = NOM_ATTR_PT_NAME_GIVEN;
			String sstr = {0};
			String* ps = 0;
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;
			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;
			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
				/* TODO   if(ix < MAXSTRSIZE_LABEL)
				dbx_mds->pollReply.pat_demog.given_name[ix] = value;*/
			}
		}
		break;

		case NOM_ATTR_PT_SEX:
		{
			dbxa.id = NOM_ATTR_PT_SEX;
			PatientSex* pps = 0;
			PatientSex ps = {0};

			ps = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatientSex)];
			pps = reinterpret_cast<PatientSex *>(dbxa.ps);
			*pps = ps;

			/* TODO 	dbx_mds->pollReply.pat_demog.patient_sex = ps;*/
		}
		break;

		case NOM_ATTR_PT_TYPE:
		{
			dbxa.id = NOM_ATTR_PT_TYPE;
			PatientType* ppt = 0;
			PatientType pt = {0};

			pt = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatientType)];
			ppt = reinterpret_cast<PatientType *>(dbxa.ps);
			*ppt = pt;

			/* TODO dbx_mds->pollReply.pat_demog.patient_type = pt;*/
		}
		break;

		case NOM_ATTR_SA_CALIB_I16:
		{
			dbxa.id = NOM_ATTR_SA_CALIB_I16;
			SaCalData16* pscd16 = 0;
			SaCalData16 scd16 = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			scd16.lower_absolute_value = mantissa | (exponent << 24);
			iindex += 4;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8)+ (buf[iindex + 3]);
			scd16.upper_absolute_value = (mantissa) | (exponent << 24);
			iindex += 4;

			scd16.lower_scaled_value = bytes2u16(&buf[iindex]);
			iindex += 2;
			scd16.upper_scaled_value = bytes2u16(&buf[iindex]);
			iindex += 2;
			scd16.increment = bytes2u16(&buf[iindex]);
			iindex+=2;
			scd16.cal_type = bytes2u16(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(SaCalData16)];
			pscd16 = reinterpret_cast<SaCalData16 *> (dbxa.ps);
			*pscd16 = scd16;
		}
		break;

		case NOM_ATTR_SA_CMPD_VAL_OBS:
		{
			dbxa.id = NOM_ATTR_SA_CMPD_VAL_OBS;
			SaObsValueCmp_intellivue sovc = {0};
			SaObsValueCmp_intellivue* psovc = 0;

			sovc.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			sovc.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			//extern DocBox_MDS dbx_mds;

			dbxa.ps = new uint8_t[sizeof(uint8_t) * (sovc.length + 4)];
			psovc = reinterpret_cast<SaObsValueCmp_intellivue *> (dbxa.ps);
			*psovc = sovc;
			for(int ix = 0; ix < sovc.count; ix++)
			{
				SaObsValue_intellivue* value = 0;
				psovc->value[ix] = new uint8_t[sizeof(uint8_t) * (bytes2u16(&buf[iindex + 4]) + 6)];
				value = reinterpret_cast<SaObsValue_intellivue *>(psovc->value[ix]);
				value->physio_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				value->state = bytes2u16(&buf[iindex]);
				iindex += 2;
				value->array.length = bytes2u16(&buf[iindex]);
				iindex += 2;
				int saveindex = iindex;
				/* TODO dbx_mds->pollReplyExt.sa_val_cmp.count = sovc.count;
				dbx_mds->pollReplyExt.sa_val_cmp.value[ix].metric_id = value->physio_id;
				dbx_mds->pollReplyExt.sa_val_cmp.value[ix].state = value->state;*/
			  /*dbx_mds->pollReplyExt.sa_val_cmp.value[ix].arr.array_size = (value->array.length) / 2;
				dbx_mds->pollReplyExt.sa_val_cmp.value[ix].updateperiod = TWO_FIFTY_SIX_MILLIS;
				dbx_mds->pollReplyExt.sa_val_cmp.value[ix].sampleperiod = (TWO_FIFTY_SIX_MILLIS / ((value->array.length) / 2));
				*/
			/*	switch(((value->array.length) / 2))
				{
					case 128:
						dbx_mds->pollReplyExt.sa_val_cmp.value[ix].wavetype = SAMPLES_500_PER_SEC;
					break;
					case 64:
						dbx_mds->pollReplyExt.sa_val_cmp.value[ix].wavetype = SAMPLES_250_PER_SEC;
					break;
					case 32:
						dbx_mds->pollReplyExt.sa_val_cmp.value[ix].wavetype = SAMPLES_125_PER_SEC;
					break;
					case 16:
						dbx_mds->pollReplyExt.sa_val_cmp.value[ix].wavetype = SAMPLES_62_POINT_5_PER_SEC;
					break;
				}*/

				for(int jx = 0; jx < value->array.length; jx++)
				{
					value->array.value[jx] = buf[iindex];
					iindex += 1;
				}
				for(int jx = 0; jx < (value->array.length) / 2; jx++)
				{
				  /* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ix].value[jx] = bytes2u16(&buf[saveindex]);*/
					saveindex += 2;
				}
			}
		}
		break;

		case NOM_ATTR_SA_RANGE_PHYS_I16:
		{
			dbxa.id = NOM_ATTR_SA_RANGE_PHYS_I16;
			ScaledRange16 sr = {0};
			ScaledRange16* psr = 0;

			sr.lower_scaled_value = bytes2u16(&buf[iindex]);
			iindex += 2;
			sr.upper_scaled_value = bytes2u16(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(ScaledRange16)];
			psr = reinterpret_cast<ScaledRange16 *>(dbxa.ps);
			*psr = sr;
		}
		break;

		case NOM_ATTR_SA_SPECN:
		{
			dbxa.id = NOM_ATTR_SA_SPECN;
			SaSpec_intellivue* pss = 0;
			SaSpec_intellivue ss = {0};

			//SavedSAattr ssa = {0};

			//extern DocBox_MDS* dbx_mds;
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.array_size = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.sample_type.sample_size = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.sample_type.significant_bits = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.flags = 0;*/

			ss.array_size = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.array_size = (uint16_t)bytes2u16(&buf[iindex]);
			ssa.saspec.array_size = (uint16_t)bytes2u16(&buf[iindex]);*/
			iindex += 2;
			ss.sample_type.sample_size = buf[iindex];
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.sample_type.sample_size = (uint8_t)buf[iindex];
			ssa.saspec.sample_type.sample_size = (uint8_t)buf[iindex];*/
			iindex += 1;
			ss.sample_type.significant_bits = buf[iindex];
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.sample_type.significant_bits = (uint8_t)buf[iindex];
			ssa.saspec.sample_type.significant_bits = (uint8_t)buf[iindex];*/
			iindex += 1;
			ss.flags = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[SaSpec_counter].saspec.flags = (uint16_t)bytes2u16(&buf[iindex]);
			ssa.saspec.flags = (uint16_t)bytes2u16(&buf[iindex]);*/

			/* TODO if(SaSpec_counter < MAX_WAVE_COUNT - 1)
				SaSpec_counter++;
*/
			dbxa.ps = new uint8_t[sizeof(SaSpec_intellivue)];
			pss = reinterpret_cast<SaSpec_intellivue *>(dbxa.ps);
			*pss = ss;
		}
		break;

		case NOM_ATTR_SA_VAL_OBS:
		{
			//extern DocBox_MDS dbx_mds;

			dbxa.id = NOM_ATTR_SA_VAL_OBS;
			SaObsValue_intellivue* psov = 0;
			SaObsValue_intellivue sov = {0};

			sov.physio_id = bytes2u16(&buf[iindex]);
			iindex += 2;
			sov.state = bytes2u16(&buf[iindex]);
			iindex += 2;
			sov.array.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].metric_id = sov.physio_id;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].state = sov.state;*/
			/*dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].arr.array_size = (sov.array.length) / 2;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].updateperiod = TWO_FIFTY_SIX_MILLIS;
			dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].sampleperiod = (TWO_FIFTY_SIX_MILLIS /((sov.array.length) / 2));
			*/
			/*
			switch(((sov.array.length) / 2))
			{
				case 128:
					dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].wavetype = SAMPLES_500_PER_SEC;
				break;
				case 64:
					dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].wavetype = SAMPLES_250_PER_SEC;
				break;
				case 32:
					dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].wavetype = SAMPLES_125_PER_SEC;
				break;
				case 16:
					dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].wavetype = SAMPLES_62_POINT_5_PER_SEC;
				break;
			}*/


			dbxa.ps = new uint8_t[sizeof(SaObsValue_intellivue) + sizeof(uint8_t) * sov.array.length - 1];
			psov = reinterpret_cast<SaObsValue_intellivue *>(dbxa.ps);
			*psov = sov;

			int saveindex = iindex;

			for(int jx = 0; jx < sov.array.length; jx++)
			{
				psov->array.value[jx] = buf[iindex];
				iindex += 1;

			}
			for(int jx = 0; jx < sov.array.length; jx++)
			{
			  /* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[dbx_mds->pollReplyExt.sa_val_cmp.count].value[jx] = bytes2u16(&buf[saveindex]);*/
				saveindex += 2;
			}

			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.count++;*/
		}
		break;

		case NOM_ATTR_SCALE_SPECN_I16:
		{
			dbxa.id = NOM_ATTR_SCALE_SPECN_I16;
			ScaleRangeSpec16_intellivue* psrs = 0;
			ScaleRangeSpec16_intellivue srs = {0};

			//extern DocBox_MDS dbx_mds;
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.lower_absolute_value = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.upper_absolute_value = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.lower_scaled_value = 0;
			dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.upper_scaled_value = 0;*/

			int8_t exponent = (int8_t)buf[iindex];
			int mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			srs.lower_absolute_value = mantissa | (exponent << 24);
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.lower_absolute_value = (uint32_t)(mantissa | (exponent << 24));
			ssa.scalespec.lower_absolute_value = (uint32_t)(mantissa | (exponent << 24));*/
			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			iindex += 4;
			int lowerAbsVal = (int)((mantissa) * pow((double)10, (double)exponent));

			int8_t exponent2 = (int8_t)buf[iindex];
			int mantissa2 = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			srs.upper_absolute_value = mantissa2 | (exponent2 << 24);

			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.upper_absolute_value = (uint32_t)(mantissa2 | (exponent2 << 24));
			ssa.scalespec.upper_absolute_value = (uint32_t)(mantissa2 | (exponent2 << 24));*/
			if (mantissa2 & 0x800000)
				mantissa2 |= ~0xffffff;

			iindex += 4;
			int upperAbsVal = (int)((mantissa2) * pow((double)10, (double)exponent2));
			srs.lower_scaled_value = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.lower_scaled_value = (uint16_t)bytes2u16(&buf[iindex]);
			ssa.scalespec.lower_scaled_value = (uint16_t)bytes2u16(&buf[iindex]);*/
			iindex += 2;
			srs.upper_scaled_value = bytes2u16(&buf[iindex]);
			/* TODO dbx_mds->pollReplyExt.sa_val_cmp.value[ScaleSpec_counter].scalespec.upper_scaled_value = (uint16_t)bytes2u16(&buf[iindex]);
			ssa.scalespec.upper_scaled_value = (uint16_t)bytes2u16(&buf[iindex]);*/

			/* TODO 	if(gSavedSAattr.size() < MAX_WAVE_COUNT)
			gSavedSAattr.push_back(ssa);*/

			/* TODO if(ScaleSpec_counter < MAX_WAVE_COUNT - 1 )
				ScaleSpec_counter++;*/

			dbxa.ps = new uint8_t[sizeof(ScaleRangeSpec16_intellivue)];
			psrs = reinterpret_cast<ScaleRangeSpec16_intellivue *>(dbxa.ps);
			*psrs = srs;
		}
		break;

		case NOM_ATTR_STD_SAFETY:
			// Not in manual
		break;

		case NOM_ATTR_SYS_ID:
		{
			dbxa.id = NOM_ATTR_SYS_ID;
			VariableLabel vl = {0};
			VariableLabel* pv1 = 0;

			// Get length of character array.
			vl.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(VariableLabel) + (sizeof(uint8_t) * vl.length - 1)];
			pv1 = reinterpret_cast<VariableLabel *>(dbxa.ps);

			*pv1 = vl;
			for(int ix = 0; ix < vl.length; ix++)
			{
				uint8_t ch = '\0';
				ch = buf[iindex];
				pv1->value[ix] = ch;
				iindex += 1;
				/* TODO if(ix < MAXSTRSIZE_LABEL)
					dbx_mds->pollReply.vms.System_Id[ix] = pv1->value[ix];*/
			}
		}
		break;

		case NOM_ATTR_SYS_SPECN:
		{
			dbxa.id = NOM_ATTR_SYS_SPECN;
			SystemSpec_intellivue* pss = 0;
			SystemSpec_intellivue ss = {0};

			ss.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			ss.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(uint8_t)*(ss.length + 4)];
			pss = reinterpret_cast<SystemSpec_intellivue *>(dbxa.ps);
			*pss = ss;

			/* TODO dbx_mds->pollReply.vms.System_Specification.count = ss.count;*/

			for(int ix = 0; ix < ss.count; ix++)
			{
				SystemSpecEntry_intellivue value = {0};
				value.component_capab_id = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.length = bytes2u16(&buf[iindex]);
				iindex += 2;

				value.value[0].count = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.value[0].length = bytes2u16(&buf[iindex]);
				iindex += 2;
				pss->value[ix] = value;

				/* TODO if(ix < MAX_SYSTEMSPECENTRIES)
				{
				  dbx_mds->pollReply.vms.System_Specification.value[ix].component_capab_id = value.component_capab_id;
					dbx_mds->pollReply.vms.System_Specification.value[ix].length = value.length;
					dbx_mds->pollReply.vms.System_Specification.value[ix].value[0].count = value.value[0].count;
				}*/

				for(int jx = 0; jx < value.value[0].count; jx++)
				{
					pss->value[ix].value[0].value[jx].object_type.partition = bytes2u16(&buf[iindex]);
					iindex += 2;
					pss->value[ix].value[0].value[jx].object_type.code = bytes2u16(&buf[iindex]);
					iindex += 2;
					pss->value[ix].value[0].value[jx].max_inst = bytes2u32(&buf[iindex]);
					iindex += 4;

					/* TODO if(jx < MAX_MDIBOBJSUPPORTENTRIES)
					{
					  dbx_mds->pollReply.vms.System_Specification.value[ix].value[0].value[jx].object_type.partition = pss->value[ix].value[0].value[jx].object_type.partition;
						dbx_mds->pollReply.vms.System_Specification.value[ix].value[0].value[jx].object_type.code = pss->value[ix].value[0].value[jx].object_type.code;
						dbx_mds->pollReply.vms.System_Specification.value[ix].value[0].value[jx].max_inst = pss->value[ix].value[0].value[jx].max_inst;
					}*/
				}
			}
		}
		break;

		case NOM_ATTR_SYS_TYPE:
		{
			dbxa.id = NOM_ATTR_SYS_TYPE;
			TYPE* pt = 0;
			TYPE t = {0};

			t.partition = bytes2u16(&buf[iindex]);
			t.code = bytes2u16(&buf[iindex + 2]);

			dbxa.ps = new uint8_t[sizeof(TYPE)];
			pt = reinterpret_cast<TYPE *>(dbxa.ps);
			*pt = t;

			/* TODO dbx_mds->pollReply.vms.System_Type.partition = t.partition;
			dbx_mds->pollReply.vms.System_Type.code = t.code;*/
		}
		break;

		case NOM_ATTR_TIME_ABS:
		{
			dbxa.id = NOM_ATTR_TIME_ABS;
			AbsoluteTime_intellivue* pabs = 0;
			AbsoluteTime_intellivue abs = {0};

			abs.century = (uint8_t)buf[iindex];
			abs.year = (uint8_t)buf[iindex + 1];
			abs.month = (uint8_t)buf[iindex + 2];
			abs.day = (uint8_t)buf[iindex + 3];
			abs.hour = (uint8_t)buf[iindex + 4];
			abs.minute = (uint8_t)buf[iindex + 5];
			abs.second = (uint8_t)buf[iindex + 6];
			abs.sec_fractions = (uint8_t)buf[iindex + 7];

			dbxa.ps = new uint8_t[sizeof(AbsoluteTime_intellivue)];
			pabs = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			*pabs = abs;

			/* TODO dbx_mds->pollReply.mds.absolute_time.century = abs.century;
			dbx_mds->pollReply.mds.absolute_time.year = abs.year;
			dbx_mds->pollReply.mds.absolute_time.month = abs.month;
			dbx_mds->pollReply.mds.absolute_time.day = abs.day;
			dbx_mds->pollReply.mds.absolute_time.hour = abs.hour;
			dbx_mds->pollReply.mds.absolute_time.minute = abs.minute;
			dbx_mds->pollReply.mds.absolute_time.second = abs.second;
			dbx_mds->pollReply.mds.absolute_time.sec_fractions = abs.sec_fractions;*/
		}
		break;

		case NOM_ATTR_TIME_PD_SAMP:
		{
			dbxa.id = NOM_ATTR_TIME_PD_SAMP;
			RelativeTime* prt = 0;
			RelativeTime rt = {0};

			rt = bytes2u32(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(RelativeTime)];
			prt = reinterpret_cast<RelativeTime *>(dbxa.ps);
			*prt = rt;
		}
		break;

		case NOM_ATTR_TIME_REL:
		{
			dbxa.id = NOM_ATTR_TIME_REL;
			RelativeTime* prt = 0;
			RelativeTime rt = {0};

			rt = bytes2u32(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(RelativeTime)];
			prt = reinterpret_cast<RelativeTime *>(dbxa.ps);
			*prt = rt;

			/* TODO dbx_mds->pollReply.mds.relative_time = rt;*/
		}
		break;

		case NOM_ATTR_TIME_STAMP_ABS:
		{
			dbxa.id = NOM_ATTR_TIME_STAMP_ABS;
			AbsoluteTime_intellivue* pabs = 0;
			AbsoluteTime_intellivue abs = {0};

			abs.century = (uint8_t)buf[iindex];
			abs.year = (uint8_t)buf[iindex + 1];
			abs.month = (uint8_t)buf[iindex + 2];
			abs.day = (uint8_t)buf[iindex + 3];
			abs.hour = (uint8_t)buf[iindex + 4];
			abs.minute = (uint8_t)buf[iindex + 5];
			abs.second = (uint8_t)buf[iindex + 6];
			abs.sec_fractions = (uint8_t)buf[iindex + 7];

			/* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.century = abs.century;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.year = abs.year;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.month = abs.month;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.day = abs.day;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.hour = abs.hour;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.minute = abs.minute;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.second = abs.second;
			dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count].abs_time.sec_fractions = abs.sec_fractions;*/

			dbxa.ps = new uint8_t[sizeof(AbsoluteTime_intellivue)];
			pabs = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			*pabs = abs;
		}
		break;

		case NOM_ATTR_TIME_STAMP_REL:
		{
			dbxa.id = NOM_ATTR_TIME_STAMP_REL;
			RelativeTime* prt = 0;
			RelativeTime rt = {0};

			rt = bytes2u32(&buf[iindex]);

			for(int kx = 1; kx <= Numeric_cmpd_count; kx++)
			{
			  /* TODO dbx_mds->pollReplyExt.nu_val_cmp.value[dbx_mds->pollReplyExt.nu_val_cmp.count - kx].rel_time = rt;*/
			}

			dbxa.ps = new uint8_t[sizeof(RelativeTime)];
			prt = reinterpret_cast<RelativeTime *>(dbxa.ps);
			*prt = rt;
		}
		break;

		case NOM_ATTR_UNIT_CODE:
		{
			dbxa.id = NOM_ATTR_UNIT_CODE;
			OIDType *poid = 0;
			OIDType oid = {0};

			oid = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(OIDType)];
			poid = reinterpret_cast<OIDType *>(dbxa.ps);
			*poid = oid;
		}
		break;

		case NOM_ATTR_VMS_MDS_STAT:
		{
			dbxa.id = NOM_ATTR_VMS_MDS_STAT;
			MDSStatus *pstat = 0;
			MDSStatus stat = {0};

			stat = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(MDSStatus)];
			pstat = reinterpret_cast<MDSStatus *>(dbxa.ps);
			*pstat = stat;
		}
		break;

		case NOM_ATTR_PT_AGE:
		{
			dbxa.id = NOM_ATTR_PT_AGE;
			/* TODO   PatMeasure* ppm = 0;
			PatMeasure pm = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			iindex += 4;

			pm.value = mantissa | (exponent << 24);

			pm.m_unit = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatMeasure)];
			ppm = reinterpret_cast<PatMeasure *> (dbxa.ps);
			*ppm = pm;

			dbx_mds->pollReply.pat_demog.patient_age.value = pm.value;
			dbx_mds->pollReply.pat_demog.patient_age.m_unit = pm.m_unit;*/
		}
		break;

		case NOM_ATTR_PT_HEIGHT:
		{
			dbxa.id = NOM_ATTR_PT_HEIGHT;
			/* TODO PatMeasure* ppm = 0;
			PatMeasure pm = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8) + (buf[iindex + 3]);
			iindex += 4;

			pm.value = mantissa | (exponent << 24);

			pm.m_unit = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatMeasure)];
			ppm = reinterpret_cast<PatMeasure *> (dbxa.ps);
			*ppm = pm;

			dbx_mds->pollReply.pat_demog.patient_height.value = pm.value;
			dbx_mds->pollReply.pat_demog.patient_height.m_unit = pm.m_unit;*/
		}
		break;

		case NOM_ATTR_PT_WEIGHT:
		{
			dbxa.id = NOM_ATTR_PT_WEIGHT;
			/* TODO PatMeasure* ppm = 0;
			PatMeasure pm = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			exponent = (int8_t)buf[iindex];
			mantissa = (buf[iindex + 1] << 16) + (buf[iindex + 2] << 8)+ (buf[iindex + 3]);
			iindex += 4;

			pm.value = mantissa | (exponent << 24);

			pm.m_unit = bytes2u16(&buf[iindex]);
			dbxa.ps = new uint8_t[sizeof(PatMeasure)];
			ppm = reinterpret_cast<PatMeasure *> (dbxa.ps);
			*ppm = pm;

			dbx_mds->pollReply.pat_demog.patient_weight.value = pm.value;
			dbx_mds->pollReply.pat_demog.patient_weight.m_unit = pm.m_unit;*/
		}
		break;

		case NOM_ATTR_SA_FIXED_VAL_SPECN:
		{
			dbxa.id = NOM_ATTR_SA_FIXED_VAL_SPECN;
			SaFixedValSpec16_intellivue* psfvs = 0;
			SaFixedValSpec16_intellivue sfvs = {0};

			sfvs.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			sfvs.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			/* TODO 	ssa.safixedspec.count = sfvs.count;
			ssa.safixedspec.length = sfvs.length;*/

			dbxa.ps = new uint8_t[sizeof(SaFixedValSpec16_intellivue) + sizeof(SaFixedValSpecEntry16_intellivue) * (sfvs.count - 1)];
			psfvs = reinterpret_cast<SaFixedValSpec16_intellivue *>(dbxa.ps);
			*psfvs = sfvs;

			for(int ix = 0; ix < sfvs.count; ix++)
			{
				SaFixedValSpecEntry16_intellivue value = {0};
				value.sa_fixed_val_id = bytes2u16(&buf[iindex]);
				/* TODO ssa.safixedspec.value[ix].sa_fixed_val_id = bytes2u16(&buf[iindex]);*/
				iindex += 2;
				value.sa_fixed_val = bytes2u16(&buf[iindex]);
				/* TODO ssa.safixedspec.value[ix].sa_fixed_val = bytes2u16(&buf[iindex]);*/
				iindex += 2;
				psfvs->value[ix] = value;
			}
		}
		break;

		case NOM_ATTR_PT_PACED_MODE:
			// Not in manual
		break;

		case NOM_ATTR_PT_ID_INT:
			// Not in manual
		break;

		case NOM_SAT_O2_TONE_FREQ:
			// Not in manual
		break;

		case NOM_ATTR_CMPD_REF_LIST:
			// Not in manual
		break;

		case NOM_ATTR_NET_ADDR_INFO:
		{
			dbxa.id = NOM_ATTR_NET_ADDR_INFO;
			IpAddressInfo* pip = 0;
			IpAddressInfo ip = {0};

			for(int ix = 0; ix < 6; ix++)
			{
				ip.mac_address.value[ix] = buf[iindex++];
			}

			for(int ix = 0; ix < 4; ix++)
			{
				ip.ip_address.value[ix] = buf[iindex++];
			}

			for(int ix = 0; ix < 4; ix++)
			{
				ip.subnet_mask.value[ix] = buf[iindex++];
			}

			dbxa.ps = new uint8_t[sizeof(IpAddressInfo)];
			pip = reinterpret_cast<IpAddressInfo *>(dbxa.ps);
			*pip = ip;

			// IP addr
			sprintf(g_smd_ipaddr, "%d", (int)ip.ip_address.value[0]);
			for(int ix = 1; ix < 4; ix++)
			{
				int	ilen = strlen(g_smd_ipaddr);
				sprintf(&g_smd_ipaddr[ilen], ".%d", (int)ip.ip_address.value[ix]);
			}
		}
		break;

		case NOM_ATTR_PCOL_SUPPORT:
		{
			dbxa.id = NOM_ATTR_PCOL_SUPPORT;
			ProtoSupport* pps = 0;
			ProtoSupport ps =
			{
				bytes2u16(&buf[iindex]),	// count
				bytes2u16(&buf[iindex + 2]),	// length
				{0}	// ProtoSupportEntry
			};
			iindex += 4;

			dbxa.ps = new uint8_t[sizeof(uint8_t) * (ps.length + 4)];
			pps = reinterpret_cast<ProtoSupport *>(dbxa.ps);
			*pps = ps;

			for (int ix = 0; ix < ps.count; ix++)
			{
				ProtoSupportEntry value = {0};
				value.appl_proto = bytes2u16(&buf[iindex]);
				value.trans_proto = bytes2u16(&buf[iindex + 2]);
				value.port_number = bytes2u16(&buf[iindex + 4]);
				value.options = bytes2u16(&buf[iindex + 6]);
				iindex += 8;
				pps->value[ix] = value;

			}
		}
		break;

		case NOM_ATTR_PT_NOTES1:
		{
			dbxa.id = NOM_ATTR_PT_NOTES1;
			String* ps = 0;
			String sstr = {0};
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;

			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;
				/* TODO if(ix < MAXSTRSIZE_PATIENT_NOTES)
					dbx_mds->pollReply.pat_demog.patient_gen_info[ix] = value;*/
			}
		}
		break;

		case NOM_ATTR_PT_NOTES2:
		{
			dbxa.id = NOM_ATTR_PT_NOTES2;
			String* ps = 0;
			String sstr = {0};
			int size = 0;

			sstr.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			size = sizeof(String) + sizeof(uint16_t) * (sstr.length - 1);
			dbxa.ps = new uint8_t[size];
			ps = reinterpret_cast<String *> (dbxa.ps);
			*ps = sstr;

			for(int ix = 0; ix < sstr.length; ix++)
			{
				uint16_t value = 0;
				value = buf[iindex];
				iindex++;
				ps->value[ix] = value;

				/* TODO if(ix < MAXSTRSIZE_PATIENT_NOTES)
					dbx_mds->pollReply.pat_demog.diagnostic_info[ix] = value;*/
			}
		}
		break;

		case NOM_ATTR_TIME_PD_POLL:
		{
			dbxa.id = NOM_ATTR_TIME_PD_POLL;
			PollDataReqPeriod* ppdrp = 0;
			PollDataReqPeriod pdrp = {0};

			pdrp.active_period = bytes2u32(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(PollDataReqPeriod)];
			ppdrp = reinterpret_cast<PollDataReqPeriod *> (dbxa.ps);
			*ppdrp = pdrp;
		}
		break;

		case NOM_ATTR_PT_BSA_FORMULA:
		{
			dbxa.id = NOM_ATTR_PT_BSA_FORMULA;
			PtBsaFormula* ppbf = 0;
			PtBsaFormula pbf = {0};

			pbf = bytes2u16(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(PtBsaFormula)];
			ppbf = reinterpret_cast<PtBsaFormula *>(dbxa.ps);
			*ppbf = pbf;
		}
		break;

		case NOM_ATTR_MDS_GEN_INFO:
		{
			dbxa.id = NOM_ATTR_MDS_GEN_INFO;
			MdsGenSystemInfo* pmgsi = 0;
			MdsGenSystemInfo mgsi = {0};

			mgsi.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			mgsi.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(uint8_t) * (mgsi.length + 4)];
			pmgsi = reinterpret_cast<MdsGenSystemInfo *>(dbxa.ps);
			*pmgsi = mgsi;

			for(int ix = 0; ix < mgsi.count; ix++)
			{
				MdsGenSystemInfoEntry value = {0};
				value.choice = bytes2u16(&buf[iindex]);
				iindex += 2;
				value.length = bytes2u16(&buf[iindex]);
				iindex += 2;

				pmgsi->value[ix] = value;
				for(int jx = 0; jx < value.length; jx++)
				{
					pmgsi->value[ix].value[jx] = buf[iindex];
					iindex++;
				}
			}
		}
		break;

		case NOM_ATTR_POLL_OBJ_PRIO_NUM:
		{
			dbxa.id = NOM_ATTR_POLL_OBJ_PRIO_NUM;
			uint16_t val = 0;
			uint16_t* pval = 0;

			val = bytes2u16(&buf[iindex]);

			dbxa.ps = new uint8_t[sizeof(uint16_t)];
			pval = reinterpret_cast<uint16_t *>(dbxa.ps);
			*pval = val;
		}
		break;

		case NOM_ATTR_POLL_NU_PRIO_LIST:
		{
			dbxa.id = NOM_ATTR_POLL_NU_PRIO_LIST;
			TextIdList *ptextIdList = 0;
			TextIdList textIdList = {0};

			textIdList.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			textIdList.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(uint8_t) * (textIdList.length + 8)];
			ptextIdList = reinterpret_cast<TextIdList *>(dbxa.ps);
			*ptextIdList = textIdList;

			for(int ix = 0; ix < textIdList.count; ix++)
			{
				TextId value = {0};
				value = bytes2u32(&buf[iindex]);
				iindex += 4;

				ptextIdList->value[ix] = value;
			}
		}
		break;

		case NOM_ATTR_POLL_RTSA_PRIO_LIST:
		{
			dbxa.id = NOM_ATTR_POLL_RTSA_PRIO_LIST;
			TextIdList* ptextIdList = 0;
			TextIdList textIdList = {0};

			textIdList.count = bytes2u16(&buf[iindex]);
			iindex += 2;
			textIdList.length = bytes2u16(&buf[iindex]);
			iindex += 2;

			dbxa.ps = new uint8_t[sizeof(uint8_t) * (textIdList.length + 8)];
			ptextIdList = reinterpret_cast<TextIdList *>(dbxa.ps);
			*ptextIdList = textIdList;

			for(int ix = 0; ix < textIdList.count; ix++)
			{
				TextId value = {0};
				value = bytes2u32(&buf[iindex]);
				iindex += 4;

				ptextIdList->value[ix] = value;
			}
		}
		break;

		case NOM_ATTR_GRP_AL_MON:
			// Not in manual
		break;

		case NOM_ATTR_GRP_METRIC_VAL_OBS:
			// Not in manual
		break;

		case NOM_ATTR_GRP_PT_DEMOG:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_APPL:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_ID:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_PROD:
			// Not in manual
		break;

		case NOM_ATTR_GRP_VMO_DYN:
			// Not in manual
		break;

		case NOM_ATTR_GRP_VMO_STATIC:
			// Not in manual
		break;

		default:
		break;
	}

	 return(dbxa);
}


/**
 * Store contents of an attribute into string form.
 * @param [in] dbxa attribute to be printed
 * @return string contianing attribute
 */
string attribute_toString(dbx_attrib dbxa)
{
	string attributeContents = "\tUnknown";
	switch(dbxa.id)
	{
		case NOM_ATTR_AL_MON_P_AL_LIST:
		{
			DevAlarmList_intellivue* pointer = reinterpret_cast<DevAlarmList_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[40] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n",
					  pointer->count,
					  pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				char val2[500] = {0};
				sprintf(val2, "\t\tal_source: %s\n\t\tal_code: %s\n\t\tal_type: %s\n\t\t"
						"al_state: %s\n\t\tManagedObjectId\n\t\t\tm_obj_class: %s\n\t\t\t"
						"context_id: %d\n\t\t\thandle: %d\n\t\t\tlength %d\n",
						 AlertSource(pointer->value[ix].al_source),
						 AlertCode(pointer->value[ix].al_code),
						 Al_Type(pointer->value[ix].al_type),
						 Al_State(pointer->value[ix].al_state),
						 ObjectClass(pointer->value[ix].object.m_obj_class),
						 (int)pointer->value[ix].object.m_obj_inst.context_id,
						 (int)pointer->value[ix].object.m_obj_inst.handle,
						 (int)pointer->value[ix].length);
				attributeContents += val2;

				char val3[500] = {0};
				switch(pointer->value[ix].alert_info_id)
				{
					case GEN_ALMON_INFO:
					{
						attributeContents += "\t\talert_info_id: GEN_ALMON_INFO\n";
						AlMonGenInfo* pointer2 = reinterpret_cast<AlMonGenInfo *>(pointer->value[ix].ps);
						sprintf(val3, "\t\tal_inst_no: %d\n\t\tal_text: %d\n\t\tpriority: %d\n\t\t"
						"flags: %d\n", (int)pointer2->al_inst_no,
						 (int)pointer2->al_text,
						 (int)pointer2->priority,
						 (int)pointer2->flags);
						attributeContents += val3;
					}
					break;
					case STR_ALMON_INFO:
					{
						attributeContents += "\t\talert_info_id: STR_ALMON_INFO\n";
						StrAlMonInfo* pointer3 = reinterpret_cast<StrAlMonInfo *>(pointer->value[ix].ps);
						sprintf(val3, "\t\tal_inst_no: %d\n\t\tal_text: %d\n\t\tpriority: %d\n\t\tflags: %d\n", (int)pointer3->al_inst_no,
						 (int)pointer3->al_text,
						 (int)pointer3->priority,
						 (int)pointer3->flags);
						attributeContents += val3;
						attributeContents += "\t\t";
						for(int ix = 0; ix < (pointer3->string.length) / 2; ix++)
							attributeContents += (char)pointer3->string.value[ix];
							attributeContents += "\n";
					}
					break;
				}
			}
		}
		break;

		case NOM_ATTR_AL_MON_T_AL_LIST:
		{
			DevAlarmList_intellivue* pointer = reinterpret_cast<DevAlarmList_intellivue* >(dbxa.ps);
			attributeContents.clear();

			char val[40] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n",
					 pointer->count,
					 pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				char val2[500] = {0};
				sprintf(val2, "\t\tal_source: %s\n\t\tal_code: %s\n\t\tal_type: %s\n\t\t"
						"al_state: %s\n\t\tManagedObjectId\n\t\t\tm_obj_class: %s\n\t\t\t"
						"context_id: %d\n\t\t\thandle: %d\n\t\tlength: %d\n",
						 AlertSource(pointer->value[ix].al_source),
						 AlertCode(pointer->value[ix].al_code),
						 Al_Type(pointer->value[ix].al_type),
						 Al_State(pointer->value[ix].al_state),
						 ObjectClass(pointer->value[ix].object.m_obj_class),
						 (int)pointer->value[ix].object.m_obj_inst.context_id,
						 (int)pointer->value[ix].object.m_obj_inst.handle,
						 (int)pointer->value[ix].length);
				attributeContents += val2;

				char val3[500] = {0};
				switch(pointer->value[ix].alert_info_id)
				{
					case GEN_ALMON_INFO:
					{
						attributeContents += "\t\talert_info_id: GEN_ALMON_INFO\n";

						AlMonGenInfo* pointer2 = reinterpret_cast<AlMonGenInfo* >(pointer->value[ix].ps);
						sprintf(val3, "\t\tal_inst_no: %d\n\t\tal_text: %d\n\t\tpriority: %d\n\t\t"
						"flags: %d\n", (int)pointer2->al_inst_no,
							(int)pointer2->al_text,
							(int)pointer2->priority,
							(int)pointer2->flags);
						attributeContents += val3;
					}
					break;
					case STR_ALMON_INFO:
					{
						attributeContents += "\t\talert_info_id: STR_ALMON_INFO\n";

						StrAlMonInfo* pointer3 = reinterpret_cast<StrAlMonInfo *>(pointer->value[ix].ps);
						sprintf(val3, "\t\tal_inst_no: %d\n\t\tal_text: %d\n\t\tpriority: %d\n\t\tflags: %d\n",
							(int)pointer3->al_inst_no,
							(int)pointer3->al_text,
							(int)pointer3->priority,
							(int)pointer3->flags);
						attributeContents += val3;
						attributeContents += "\t\t";
						for(int jx = 0; jx < (pointer3->string.length) / 2; jx++)
							attributeContents += (char)pointer3->string.value[jx];
							attributeContents += "\n";
					}
					break;
				}
			}
		}
		break;

		case NOM_ATTR_ALTITUDE:
		{
			uint16_t* pointer = reinterpret_cast<uint16_t *>(dbxa.ps);
			attributeContents.clear();
			char val[30] = {0};
			sprintf(val, "\taltitude: %d\n", *pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_AREA_APPL:
		{
			ApplicationArea* pointer = reinterpret_cast<ApplicationArea *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tApplicationArea: ";
			attributeContents += AppArea(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_COLOR:
		{
			SimpleColour* pointer = reinterpret_cast<SimpleColour *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tSimpleColour: " ;
			attributeContents += Color(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_DEV_AL_COND:
		{
			DeviceAlertCondition* pointer = reinterpret_cast<DeviceAlertCondition *>(dbxa.ps);
			attributeContents.clear();

			char val[500] = {0};
			sprintf(val, "\tdevice_alert_state: %s\n\tal_stat_chg_cnt: %d\n\tmax_p_alarm: %s\n\tmax_t_alarm: %s\n\tmax_aud_alarm: %s\n",
					Dev_Al_State(pointer->device_alert_state),
					pointer->al_stat_chg_cnt,
					Al_Type(pointer->max_p_alarm),
					Al_Type(pointer->max_t_alarm),
					Al_Type(pointer->max_aud_alarm));
			attributeContents += val;
		}
		break;

		case NOM_ATTR_DISP_RES:
		{
			DispResolution_intellivue* pointer = reinterpret_cast<DispResolution_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[200] = {0};
			sprintf(val, "\tnumbers before decimal: %d\n\tnumbers after decimal: %d", pointer->pre_point, pointer->post_point);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_GRID_VIS_I16:
		{
			SaVisualGrid16* pointer = reinterpret_cast<SaVisualGrid16 *>(dbxa.ps);
			attributeContents.clear();

			char val[50] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n", pointer->count, pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				uint8_t Fval[4] = {0};
				int8_t exponent = 0;
				int mantissa = 0;

				int24bytes(&Fval[0], pointer->value[ix].absolute_value);
				exponent = (int8_t)Fval[0];
				mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

				if (mantissa & 0x800000)
					mantissa |= ~0xffffff;

				char val2[50] = {0};
				sprintf(val2, "\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
				attributeContents += val2;

				float answer = (float)((mantissa) * pow(double(10), (double)exponent));
				switch(mantissa)
				{
					case 0x7fffff:
						attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
					break;
					case 0x800000:
						attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
					break;
					case 0x7ffffe: case 0x800002:
						attributeContents += "\tabsolute_value: +/- INFINITY\n";
					break;
					default:
					{
						char val3[50] = {0};
						sprintf(val3, "\tabsolute_value: %f\n", answer);
						attributeContents += val3;
					}
					break;
				}

				char val4[100] = {0};
				sprintf(val4, "\tscaled_value: %d\n\tlevel: %d\n", pointer->value[ix].scaled_value, pointer->value[ix].level);
				attributeContents += val4;
			}
		}
		break;

		case NOM_ATTR_ID_ASSOC_NO:
		{
			uint16_t* pointer = reinterpret_cast<uint16_t *>(dbxa.ps);
			attributeContents.clear();
			char val[50] = {0};
			sprintf(val, "\t%d\n", *pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_ID_BED_LABEL:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_ID_HANDLE:
		{
			Handle* pointer = reinterpret_cast<Handle *>(dbxa.ps);
			attributeContents.clear();
			char val[50] = {0};
			sprintf(val, "\thandle: %d\n", *pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_ID_LABEL:
		{
			TextId* pointer = reinterpret_cast<TextId *>(dbxa.ps);
			attributeContents.clear();
			attributeContents += "\tTextId: ";
			attributeContents += TextIdName(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_ID_LABEL_STRING:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_ID_MODEL:
		{
			SystemModel_intellivue* pointer = reinterpret_cast<SystemModel_intellivue *>(dbxa.ps);
			attributeContents.clear();

			VariableLabel* man = reinterpret_cast<VariableLabel *>(pointer->manufacturer);

			char val[100] = {0};
			sprintf(val, "\t  manufacturer: length=%3hu, val=", man->length);
			attributeContents += val;

			for (int iy = 0; iy < man->length; iy++)
			{
				attributeContents += (char)man->value[iy];
			}
			attributeContents += "\n";

			VariableLabel* mod = reinterpret_cast<VariableLabel *>(pointer->model_number);

			char val2[100] = {0};
			sprintf(val2, "\t  model_number: length=%3hu, val=", mod->length);
			attributeContents += val2;

			for (int iy = 0; iy < mod->length; iy++)
			{
				attributeContents += (char)mod->value[iy];
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_ID_PROD_SPECN:
		{
			ProductionSpec_intellivue* pointer = reinterpret_cast<ProductionSpec_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[50] = {0};
			sprintf(val, "\tproduction spec: count=%hu, length=%hu\n",
				pointer->count,
				pointer->length);
			attributeContents += val;

			for (int ix = 0; ix < pointer->count; ix++)
			{
				VariableLabel* vl = 0;
				vl = reinterpret_cast<VariableLabel *>(pointer->value[ix].prod_spec);

				char val2[500] = {0};
				sprintf(val2, "\t  type=%s\n\tcomponent id= %s (%3hd)\n\t len=%4hu\n\t val=",
					SpecType(pointer->value[ix].spec_type),
					componentID(pointer->value[ix].component_id),
					pointer->value[ix].component_id,
					vl->length);
				attributeContents += val2;

				for (int iy = 0; iy < vl->length; iy++)
				{
					attributeContents += (char)vl->value[iy];
				}
				attributeContents += "\n";
			}
		}
		break;

		case NOM_ATTR_ID_TYPE:
		{
			TYPE* pointer = reinterpret_cast<TYPE *>(dbxa.ps);
			attributeContents.clear();

			char type[200] = {0};
			sprintf(type, "\tpartition= %s (%d), code= %s\n" ,
					PartitionName(pointer->partition),
					(uint32_t)pointer->partition,
					CodeName(pointer->code));
			attributeContents += type;
		}
		break;

		case NOM_ATTR_LINE_FREQ:
		{
			LineFrequency* pointer = reinterpret_cast<LineFrequency *>(dbxa.ps);
			attributeContents.clear();

			switch(*pointer)
			{
				case 0:
					attributeContents += "\tLINE_F_UNSPEC\n";
				break;
				case 1:
					attributeContents += "\tLINE_F_50HZ\n";
				break;
				case 2:
					attributeContents += "\tLINE_F_60HZ\n";
				break;
				default:
					attributeContents += "\tUnknown\n";
				break;
			}
		}
		break;

		case NOM_ATTR_LOCALIZN:
		{
			SystemLocal* pointer = reinterpret_cast<SystemLocal *>(dbxa.ps);
			attributeContents.clear();

			uint8_t Fval[4] = {0};
			int24bytes(&Fval[0], pointer->text_catalog_revision);

			char val[50] = {0};
			sprintf(val, "\t  text catalog version= %d.%d\n", (uint32_t)Fval[0], (uint32_t)Fval[1]);
			attributeContents += val;

			char val2[50] = {0};
			sprintf(val2, "\t  language revision= %d.%d\n", (uint32_t)Fval[2], (uint32_t)Fval[3]);
			attributeContents += val2;

			attributeContents += "\t  language= ";
			attributeContents += Lang(pointer->language);
			attributeContents += "\n";

			switch(pointer->format)
			{
				case 11:
					attributeContents += "\tSTRFMT_UNICODE_NT\n";
				break;
				default:
					attributeContents += "\tUnknown\n";
				break;
			}
		}
		break;

		case NOM_ATTR_METRIC_INFO_LABEL:
		{
			TextId* pointer = reinterpret_cast<TextId *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tTextId: ";
			attributeContents += TextIdName(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_METRIC_INFO_LABEL_STR:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_METRIC_SPECN:
		{
			/*MetricSpec* pointer = reinterpret_cast<MetricSpec *>(dbxa.ps);
			attributeContents.clear();

			string temp;
			temp += "\tMetricSpec\n";

			char update[30] = {0};
			sprintf(update, "\t\tupdate_period: %d\n", (uint32_t)pointer->update_period);
			temp += update;

			temp += "\t\tcategory: ";
			temp +=  MetricCat(pointer->category);
			temp += "\n";

		    temp += "\t\taccess: ";
			temp += MetAccess(pointer->access);
			temp += "\n";

			char str[30] = {0};
			sprintf(str, "\t\tms_struct: %d\n", (uint32_t)pointer->structure.ms_struct);
			temp += str;

			char comp[30] = {0};
			sprintf(comp, "\t\tms_comp_no: %d\n", (uint32_t)pointer->structure.ms_comp_no);
			temp += comp;

			char rel[30] = {0};
			sprintf(rel, "\t\trelevance: %d\n", (uint32_t)pointer->relevance);
			temp += rel;
			attributeContents = temp;
      */
		  attributeContents = "NOM_ATTR_METRIC_SPECN TODO\n";
		}
		break;

		case NOM_ATTR_METRIC_STAT:
		{
			MetricState* pointer = reinterpret_cast<MetricState *>(dbxa.ps);
			attributeContents.clear();

			char val[50] = {0};
			if(*pointer == METRIC_OFF)
			{
				sprintf(val,"\tMETRIC_OFF  (%d)\n", (uint32_t)*pointer);
				attributeContents += val;
			}
			else
			{
				sprintf(val, "\tMETRIC_ON  (%d)\n", (uint32_t)*pointer);
				attributeContents += val;
			}
		}
		break;

		case NOM_ATTR_MODE_MSMT:
		{
			MeasureMode* pointer = reinterpret_cast<MeasureMode *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tMeasureMode: ";

			attributeContents +=  MMode(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_MODE_OP:
		{
			PrivateOID* pointer = reinterpret_cast<PrivateOID *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tPrivateOID: ";
			attributeContents += OpMode(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_NOM_VERS:
		{
			uint32_t* pointer = reinterpret_cast<uint32_t *>(dbxa.ps);
			attributeContents.clear();

			uint8_t Fval[4] = {0};
			int24bytes(&Fval[0], *pointer);
			uint32_t major = bytes2u16(&Fval[0]);
			uint32_t minor = bytes2u16(&Fval[2]);

			char val[50] = {0};
			sprintf(val,"\tnomenclature version: %d.%d\n", major, minor);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_NU_CMPD_VAL_OBS:
		{
			NuObsValueCmp_intellivue* pointer = reinterpret_cast<NuObsValueCmp_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[100] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n",
					(uint32_t)pointer->count,
					(uint32_t)pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				char val2[300] = {0};
				int8_t exponent = 0;
				int mantissa = 0;
				uint8_t Fval[4] = {0};

				sprintf(val2, "\tphysio_id: %s\n\tstate: %s (%d)\n\tunit_code: %s\n",
					PhysioIdName((uint32_t)pointer->value[ix].physio_id),
					MeasureStat((uint32_t)pointer->value[ix].state),
					(uint32_t)pointer->value[ix].state,
					UnitCode((uint32_t)pointer->value[ix].unit_code));
				attributeContents += val2;

				int24bytes(&Fval[0], (uint32_t)pointer->value[ix].value);
				exponent = (int8_t)Fval[0];
				mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

				if (mantissa & 0x800000)
					mantissa |= ~0xffffff;

				char val3[100] = {0};
				sprintf(val3, "\texponent: %d\n\tmantissa: %d\n", (int)exponent, (int)mantissa);
				attributeContents += val3;

				float answer = (float)(((int)mantissa) * pow(double(10), (double)(int)exponent));
				switch(mantissa)
				{
					case 0x7fffff:
						attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
					break;
					case 0x800000:
						attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
					break;
					case 0x7ffffe:
						attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
					break;
					case 0x800002:
						attributeContents += "\tabsolute_value: +/- INFINITY\n";
					break;
					default:
					{
						char ans[50] = {0};
						sprintf(ans, "\tabsolute value: %f\n", answer);
						attributeContents += ans;
					}
					break;
				}
			}
			attributeContents += "-----end-------";
		}
		break;

		case NOM_ATTR_NU_VAL_OBS:
		{
			uint8_t Fval[4] = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			NuObsValue_intellivue* pointer = reinterpret_cast<NuObsValue_intellivue *>(dbxa.ps);
			attributeContents.clear();

			int24bytes(&Fval[0], pointer->value);
			exponent = (int8_t)Fval[0];
			mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			char val[300] = {0};
			sprintf(val, "\tphysio_id: %s\n\tstate: %s\n\tunit_code: %s\n",
					PhysioIdName((uint32_t)pointer->physio_id),
					MeasureStat((uint32_t)pointer->state),
					UnitCode((uint32_t)pointer->unit_code));
			attributeContents += val;

			char val2[50] = {0};
			sprintf(val2,"\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val2;

			float answer = (float)((mantissa) * pow((double)10, (double)exponent));

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
				{
					char ans[50] = {0};
					sprintf(ans, "\tabsolute value: %f\n", answer);
					attributeContents += ans;
				}
				break;
			}
		}
		break;

		case NOM_ATTR_PT_BSA:
		{
			uint8_t Fval[4] = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			/*PatMeasure* pointer = reinterpret_cast<PatMeasure *>(dbxa.ps);
			attributeContents.clear();

			int24bytes(&Fval[0], pointer->value);
			exponent = (int8_t)Fval[0];
			mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			char val[50] = {0};
			sprintf(val,"\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			int answer = (int)((mantissa) * pow(double(10), (double)exponent));

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
				{
					char ans[20] = {0};
					sprintf(ans, "\tvalue: %d\n", answer);
					attributeContents += ans;
				}
				break;
			}

			attributeContents += "\tm_unit: ";
			attributeContents += UnitCode(pointer->m_unit);
			attributeContents +='\n';*/
			attributeContents = "NOM_ATTR_PT_BSA TODO\n";
		}
		break;

		case NOM_ATTR_PT_DEMOG_ST:
		{
			PatDmgState* pointer = reinterpret_cast<PatDmgState *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tPatDmgState: ";
			attributeContents += PatDemogState(*pointer);
			attributeContents += "\n";

		}
		break;

		case NOM_ATTR_PT_DOB:
		{
			AbsoluteTime_intellivue* pointer = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[500] = {0};
			sprintf(val, "\tDOB\n\t\tcentury: %d\n\t\tyear %d\n\t\tmonth: %d\n\t\tday: %d\n\t\thour: %d\n\t\tminute:"
							"%d\n\t\tsecond: %d\n\t\tsec_fractions: %d\n",
						(uint32_t)pointer->century,
						(uint32_t)pointer->year,
						(uint32_t)pointer->month,
						(uint32_t)pointer->day,
						(uint32_t)pointer->hour,
						(uint32_t)pointer->minute,
						(uint32_t)pointer->second,
						(uint32_t)pointer->sec_fractions);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_PT_ID:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int i = 0; i < pointer->length; i++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[i]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_PT_NAME_FAMILY:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_PT_NAME_GIVEN:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", (char)pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_PT_SEX:
		{
			PatientSex* pointer = reinterpret_cast<PatientSex *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tpatient sex: " ;
			attributeContents += PatSex(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_PT_TYPE:
		{
			PatientType* pointer = reinterpret_cast<PatientType *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tPatientType: ";
			attributeContents += PatType(*pointer);
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_SA_CALIB_I16:
		{
			SaCalData16* pointer = reinterpret_cast<SaCalData16 *>(dbxa.ps);
			attributeContents.clear();

			uint8_t Fval[4] = {0};
			int24bytes(&Fval[0], pointer->lower_absolute_value);
			int8_t exponent = (int8_t)Fval[0];
			int mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			int lowerAbsVal = (int)((mantissa) * pow(double(10), (double)exponent));

			int24bytes(&Fval[0], pointer->upper_absolute_value);
			int8_t exponent2 = (int8_t)Fval[0];
			int mantissa2 = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa2 & 0x800000)
				mantissa2 |= ~0xffffff;

			int upperAbsVal = (int)((mantissa2) * pow(double(10), (double)exponent2));

			char val[50] = {0};
			sprintf(val, "\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY";
				break;
				default:
				{
					char low[50] = {0};
					sprintf(low, "\tlower_absolute_value: %d\n", lowerAbsVal);
					attributeContents +=low;
				}
				break;
			}

			char val2[50] = {0};
			sprintf(val2, "\texponent: %d\n\tmantissa: %d\n", exponent2, mantissa2);
			attributeContents += val2;

			switch(mantissa2)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY" ;
				break;
				default:
					char up[50] = {0};
					sprintf(up, "\tupper_absolute_value: %d\n", upperAbsVal);
					attributeContents += up;
				break;
			}

			char val3[100] = {0};
			sprintf(val3, "\tlower_scaled_value: %d\n\tupper_scaled_value: %d\n\tincrement %d\n\tcal_type: ",
					pointer->lower_scaled_value,
					pointer->upper_scaled_value,
					pointer->increment);
			attributeContents += val3;

			switch(pointer->cal_type)
			{
				case 0:
					attributeContents += "BAR\n";
				break;
				case 1:
					attributeContents += "STAIR\n";
				break;
				default:
					attributeContents += "shouldn't be reached\n";
				break;
			}
		}
		break;

		case NOM_ATTR_SA_CMPD_VAL_OBS:
		{
			SaObsValueCmp_intellivue* pointer = reinterpret_cast<SaObsValueCmp_intellivue *>(dbxa.ps);
			attributeContents.clear();

			for(int ix = 0; ix < pointer->count; ix++)
			{
				SaObsValue_intellivue* pointer2 = reinterpret_cast<SaObsValue_intellivue *>(pointer->value[ix]);

				char val[300] = {0};
				sprintf(val, "\tphysio_id: %s\n\tstate: %s\n\tlength: %d\n",
						PhysioIdName((int)pointer2->physio_id),
						MeasureStat(pointer2->state),
						pointer2->array.length);
						attributeContents += val;
				attributeContents += "\tarray values\n";
				attributeContents += "\t";

				for(int jx = 0; jx < pointer2->array.length; jx++)
				{
					char val2[20] = {0};
					if(jx % 20 == 0)
						sprintf(val2, "\n\t%d ", (int)bytes2u16(&(pointer2->array.value[jx])));
					else
						sprintf(val2, "%d ", (int)bytes2u16(&(pointer2->array.value[jx])));
					jx++;
					attributeContents += val2;
				}
				attributeContents += "\n";
			}
		}
		break;

		case NOM_ATTR_SA_RANGE_PHYS_I16:
		{
			ScaledRange16* pointer = reinterpret_cast<ScaledRange16 *>(dbxa.ps);
			attributeContents.clear();

			char val[100] = {0};
			sprintf(val, "\tlower_scaled_value: %d\n\tupper_scaled_value: %d\n",
					pointer->lower_scaled_value,
					pointer->upper_scaled_value);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_SA_SPECN:
		{
			SaSpec_intellivue* pointer = reinterpret_cast<SaSpec_intellivue *>(dbxa.ps);
			attributeContents.clear();
			attributeContents.erase (attributeContents.begin(), attributeContents.end());
			char temp[500] = {0};

			char size[20] = {0};
			sprintf(size, "\tarray size: %d\n", (uint32_t)pointer->array_size);
			strcat(temp, size);

			char samp[20] = {0};
			sprintf(samp, "\tsample size: %d\n", (uint32_t)pointer->sample_type.sample_size);
			strcat(temp, samp);

			char sig[50] = {0};
			sprintf(sig, "\tsignificant bits: %d\n", (uint32_t)pointer->sample_type.significant_bits);
			strcat(temp, sig);

			strcat(temp, "\tflags: ");
			strcat(temp, Flags(pointer->flags));
			strcat(temp, "\n");

			attributeContents = (string) temp;
		}
		break;

		case NOM_ATTR_SA_VAL_OBS:
		{
			SaObsValue_intellivue* pointer = reinterpret_cast<SaObsValue_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[100] = {0};
			sprintf(val, "\tphysio_id: %s\n\tstate: %s\n\tlength: %d\n",
					PhysioIdName((int)pointer->physio_id),
					MeasureStat(pointer->state),
					pointer->array.length);
			attributeContents += val;
			attributeContents += "\tarray values\n";
			attributeContents += "\t";

			for(int jx = 0; jx < pointer->array.length; jx++)
			{
				char val2[20] = {0};
				if(jx % 20 == 0)
					sprintf(val2, "\n\t%d ", (int)bytes2u16(&(pointer->array.value[jx])));
				else
					sprintf(val2, "%d ", (int)bytes2u16(&(pointer->array.value[jx])));
				attributeContents += val2;
				jx++;
			}
			attributeContents += "\n";
		}
		break;

		case NOM_ATTR_SCALE_SPECN_I16:
		{
			ScaleRangeSpec16_intellivue* pointer = reinterpret_cast<ScaleRangeSpec16_intellivue *>(dbxa.ps);
			attributeContents.clear();

			uint8_t Fval[4] = {0};
			int24bytes(&Fval[0], pointer->lower_absolute_value);
			int exponent = (int8_t)Fval[0];
			int mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			float lowerAbsVal = (float)((mantissa) * pow(double(10), (double)exponent));

			int24bytes(&Fval[0], pointer->upper_absolute_value);
			int exponent2 = (int8_t)Fval[0];
			int mantissa2 = (Fval[1] << 16) + ( Fval[2] << 8) + (Fval[3]);

			if (mantissa2 & 0x800000)
				mantissa2 |= ~0xffffff;

			float upperAbsVal = (float)((mantissa2) * pow(double(10), (double)exponent2));

			char val[50] = {0};
			sprintf(val, "\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n";
				break;
				default:
				{
					char low[50] = {0};
					sprintf(low, "\tlower_absolute_value: %7.2f\n", lowerAbsVal);
					attributeContents += low;
				}
				break;
			}

			char val2[50] = {0};
			sprintf(val2, "\texponent: %d\n\tmantissa: %d\n", exponent2, mantissa2);
			attributeContents += val2;

			switch(mantissa2)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
					char up[50] = {0};
					sprintf(up, "\tupper_absolute_value: %f\n", upperAbsVal);
					attributeContents += up;
				break;
			}

			char val3[100] = {0};
			sprintf(val3, "\tlower_scaled_value: %d\n\tupper_scaled_value: %d\n",
					pointer->lower_scaled_value,
					pointer->upper_scaled_value);
			attributeContents += val3;
		}
		break;

		case NOM_ATTR_STD_SAFETY:
			// Not in manual
		break;

		case NOM_ATTR_SYS_ID:
		{
			VariableLabel* pointer = reinterpret_cast<VariableLabel *>(dbxa.ps);
			attributeContents.clear();
			attributeContents += "\t";

			for(int ix = 0; ix < pointer->length; ix++)
			{
				char val[10] = {0};
				sprintf(val, "%c", pointer->value[ix]);
				attributeContents += val;
			}
			attributeContents += "\n";
		}
		break;
		case NOM_ATTR_SYS_SPECN:
		{
			SystemSpec_intellivue* pointer = reinterpret_cast<SystemSpec_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[60] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n",
					pointer->count,
					pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				char val2[100] = {0};
				sprintf(val2, "\t\tcomponent_capab_id: %s\n\t\tlength: %d\n\t\tcount: %d\n\t\tlength: %d\n",
						get_profile_id_name(pointer->value[ix].component_capab_id),
						pointer->value[ix].length,
						pointer->value[ix].value[0].count,
						pointer->value[ix].value[0].length);
				attributeContents += val2;

				for(int jx = 0; jx < pointer->value[ix].value[0].count; jx++)
				{
					char val3[100] = {0};
					sprintf(val3, "\t\t\tpartition: %s\n\t\t\tcode: %s\n\t\t\tmax_inst: %d\n",
							PartitionName(pointer->value[ix].value[0].value[jx].object_type.partition),
							CodeName(pointer->value[ix].value[0].value[jx].object_type.code),
							pointer->value[ix].value[0].value[jx].max_inst);
					attributeContents += val3;
				}
			}
		}
		break;

		case NOM_ATTR_SYS_TYPE:
		{
			TYPE* pointer = reinterpret_cast<TYPE *>(dbxa.ps);
			attributeContents.clear();

			char val[80] = {0};
			sprintf(val, "\tpartition=%s (%d), code=%s\n",
					PartitionName(pointer->partition),
					pointer->partition,
					CodeName(pointer->code));
			attributeContents += val;
		}
		break;

		case NOM_ATTR_TIME_ABS:
		{
			AbsoluteTime_intellivue* pointer = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[500] = {0};
			sprintf(val, "\tcentury: %d\n\tyear %d\n\tmonth: %d\n\tday: %d\n\thour: %d\n\tminute:"
							"%d\n\tsecond: %d\n\tsec_fractions: %d\n",
						(uint32_t)pointer->century,
						(uint32_t)pointer->year,
						(uint32_t)pointer->month,
						(uint32_t)pointer->day,
						(uint32_t)pointer->hour,
						(uint32_t)pointer->minute,
						(uint32_t)pointer->second,
						(uint32_t)pointer->sec_fractions);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_TIME_PD_SAMP:
		{
			RelativeTime* pointer = reinterpret_cast<RelativeTime *>(dbxa.ps);
			attributeContents.clear();

			char val[40] = {0};
			sprintf(val, "\trelative time: %d\n", *pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_TIME_REL:
		{
			RelativeTime* pointer = reinterpret_cast<RelativeTime *>(dbxa.ps);
			attributeContents.clear();

			char val[40] = {0};
			sprintf(val, "\trelative time: %d\n", *pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_TIME_STAMP_ABS:
		{
			AbsoluteTime_intellivue* pointer = reinterpret_cast<AbsoluteTime_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[500] = {0};
			sprintf(val, "\tDOB\n\t\tcentury: %d\n\t\tyear %d\n\t\tmonth: %d\n\t\tday: %d\n\t\thour: %d\n\t\tminute:"
							"%d\n\t\tsecond: %d\n\t\tsec_fractions: %d\n",
						pointer->century,
						pointer->year,
						pointer->month,
						pointer->day,
						pointer->hour,
						pointer->minute,
						pointer->second,
						pointer->sec_fractions);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_TIME_STAMP_REL:
		{
			RelativeTime* pointer = reinterpret_cast<RelativeTime *>(dbxa.ps);
			attributeContents.clear();

			char val[40] = {0};
			sprintf(val, "\trelative time: %d\n", (uint32_t)*pointer);
			attributeContents += val;
		}
		break;

		case NOM_ATTR_UNIT_CODE:
		{
			OIDType* pointer = reinterpret_cast<OIDType *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tunit_code: ";
			attributeContents += UnitCode(*pointer);
			attributeContents += '\n';
		}
		break;
		case NOM_ATTR_VMS_MDS_STAT:
		{
			MDSStatus* pointer = reinterpret_cast<MDSStatus *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tstatus: ";
			attributeContents += MdsStatus(*pointer);
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_PT_AGE:
		{
			uint8_t Fval[4] = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			/*PatMeasure* pointer = reinterpret_cast<PatMeasure *>(dbxa.ps);
			attributeContents.clear();

			int24bytes(&Fval[0], pointer->value);
			exponent = (int8_t)Fval[0];
			mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			char val[50] = {0};
			sprintf(val, "\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			int answer = (int)((mantissa) * pow(double(10), (double)exponent));

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
				{
					char ans[50] = {0};
					sprintf(ans, "\tvalue: %d\n", answer);
					attributeContents += ans;
				}
				break;
			}

			attributeContents += "\tm_unit: ";
			attributeContents += UnitCode(pointer->m_unit);
			attributeContents +='\n';*/
			attributeContents = "NOM_ATTR_PT_AGE TODO\n";
		}
		break;

		case NOM_ATTR_PT_HEIGHT:
		{
			uint8_t Fval[4] = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			/*PatMeasure* pointer = reinterpret_cast<PatMeasure *>(dbxa.ps);
			attributeContents.clear();


			int24bytes(&Fval[0], pointer->value);
			exponent = (int8_t)Fval[0];
			mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			char val[50] = {0};
			sprintf(val,"\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			int answer = (int)((mantissa) * pow(double(10), (double)exponent));

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
				{
					char ans[50] = {0};
					sprintf(ans, "\tvalue: %d\n", answer);
					attributeContents += ans;
				}
				break;
			}

			attributeContents += "\tm_unit: ";
			attributeContents += UnitCode(pointer->m_unit);
			attributeContents +='\n';*/
			attributeContents = "NOM_ATTR_PT_HEIGHT TODO\n";
		}
		break;

		case NOM_ATTR_PT_WEIGHT:
		{
			uint8_t Fval[4] = {0};
			int8_t exponent = 0;
			int mantissa = 0;

			/*PatMeasure* pointer = reinterpret_cast<PatMeasure *>(dbxa.ps);
			attributeContents.clear();

			int24bytes(&Fval[0], pointer->value);
			exponent = (int8_t)Fval[0];
			mantissa = (Fval[1] << 16) + (Fval[2] << 8) + (Fval[3]);

			if (mantissa & 0x800000)
				mantissa |= ~0xffffff;

			char val[50] = {0};
			sprintf(val, "\texponent: %d\n\tmantissa: %d\n", exponent, mantissa);
			attributeContents += val;

			int answer = (int)((mantissa) * pow(double(10), (double)exponent));

			switch(mantissa)
			{
				case 0x7fffff:
					attributeContents += "\tabsolute_value: NaN (Not a Number)\n";
				break;
				case 0x800000:
					attributeContents += "\tabsolute_value: NRes (Not at this resolution)\n";
				break;
				case 0x7ffffe: case 0x800002:
					attributeContents += "\tabsolute_value: +/- INFINITY\n" ;
				break;
				default:
				{
					char ans[50] = {0};
					sprintf(ans, "\tvalue: %d\n", answer);
					attributeContents += ans;
				}
				break;
			}

			attributeContents += "\tm_unit: ";
			attributeContents += UnitCode(pointer->m_unit);
			attributeContents +='\n';*/
			attributeContents = "NOM_ATTR_PT_WEIGHT TODO\n";
		}
		break;

		case NOM_ATTR_SA_FIXED_VAL_SPECN:
		{
			SaFixedValSpec16_intellivue* pointer = reinterpret_cast<SaFixedValSpec16_intellivue *>(dbxa.ps);
			attributeContents.clear();

			char val[50] = {0};
			sprintf(val, "\tcount: %d\n\tlength: %d\n",
					pointer->count,
					pointer->length);
			attributeContents += val;

			for(int ix = 0; ix < pointer->count; ix++)
			{
				attributeContents += "\t\tsa_fixed_val_id: ";
				attributeContents += SaFixedId(pointer->value[ix].sa_fixed_val_id);
				attributeContents += '\n';
				attributeContents += "\t\tsa_fixed_val: ";

				char val2[10] = {0};
				sprintf(val2, "%d", (int)pointer->value[ix].sa_fixed_val);
				attributeContents += val2;
				attributeContents += '\n';
			}
		}
		break;

		case NOM_ATTR_PT_PACED_MODE:
			// Not in manual
		break;

		case NOM_ATTR_PT_ID_INT:
			// Not in manual
		break;

		case NOM_SAT_O2_TONE_FREQ:
			// Not in manual
		break;

		case NOM_ATTR_CMPD_REF_LIST:
			// Not in manual
		break;

		case NOM_ATTR_NET_ADDR_INFO:
		{
			IpAddressInfo* pointer = reinterpret_cast<IpAddressInfo *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tmac, ip, subnet mask=\n";

			// MAC
			char val[10];
			sprintf(val, "%02X", (int)pointer->mac_address.value[0]);
			attributeContents += val;

			for (int ix = 1; ix < 6; ix++)
			{
				sprintf(val, ":%02X", (int)pointer->mac_address.value[ix]);
				attributeContents += val;
			}

			// IP addr
			sprintf(g_smd_ipaddr, "%d", (int)pointer->ip_address.value[0]);
			for (int ix = 1; ix < 4; ix++)
			{
				int ilen = strlen(g_smd_ipaddr);
				sprintf(&g_smd_ipaddr[ilen], ".%d", (int)pointer->ip_address.value[ix]);
			}
			attributeContents += g_smd_ipaddr;

			// Subnet mask
			char val2[10];
			sprintf(val2, ", %d", (int)pointer->subnet_mask.value[0]);
			attributeContents += val2;

			for (int ix = 1; ix < 4; ix++)
			{
				sprintf(val2, ".%d", (int)pointer->subnet_mask.value[ix]);
				attributeContents += val2;
			}

			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_PCOL_SUPPORT:
		{
			ProtoSupport* pointer = reinterpret_cast<ProtoSupport *>(dbxa.ps);
			stringstream ss;

			attributeContents.clear();
			attributeContents += "\tcount=";
			ss << (uint16_t)(pointer->count);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += ", length=";
			ss << (uint16_t)(pointer->length);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += '\n';

			for (int ix = 0; ix < pointer->count; ix++)
			{
				if (pointer->value[ix].appl_proto == AP_ID_DATA_OUT)
				{
					attributeContents +=
					"\n\t  The following entry specifies the port for the Data Export"
					"\n\t  Protocol. The corresponding Association Control Protocol"
					"\n\t  runs on the same port."
					"\n\n\t  Client must only send requests to the port specified for"
					"\n\t  the Data Export Protocol.\n";
				}

				attributeContents += "\t  appl_proto=";
				ss << (uint16_t)( pointer->value[ix].appl_proto);
				attributeContents += ss.str();
				ss.str("");
				attributeContents += ", trans_proto=";
				ss << (uint16_t)( pointer->value[ix].trans_proto);
				attributeContents += ss.str();
				ss.str("");
				attributeContents += ", port number=";
				ss << (uint16_t)( pointer->value[ix].port_number);
				attributeContents += ss.str();
				ss.str("");
				char options[20] = {0};
				sprintf(options, ", options=0x%04hX", pointer->value[ix].options);
				attributeContents += options;
				attributeContents += '\n';
			}
		}
		break;

		case NOM_ATTR_PT_NOTES1:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tnotes1\n";
			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				attributeContents += (char)pointer->value[ix];
			}
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_PT_NOTES2:
		{
			String* pointer = reinterpret_cast<String *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tnotes2\n";
			attributeContents += "\t";
			for(int ix = 0; ix < pointer->length; ix++)
			{
				attributeContents += (char)pointer->value[ix];
			}
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_TIME_PD_POLL:
		{
			PollDataReqPeriod* pointer = reinterpret_cast<PollDataReqPeriod *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tactive period: ";
			stringstream ss;
			ss << (int)(pointer->active_period);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_PT_BSA_FORMULA:
		{
			PtBsaFormula* pbf = reinterpret_cast<PtBsaFormula *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tPtBsaFormula: ";
			attributeContents += BsaFormula(*pbf);
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_MDS_GEN_INFO:
		{
			MdsGenSystemInfo* mgsi = reinterpret_cast<MdsGenSystemInfo *>(dbxa.ps);
			attributeContents.clear();

			// Count
			attributeContents += "\tcount: ";
			stringstream ss;
			ss << (int)(mgsi->count);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += '\n';

			// Length
			attributeContents += "\tlength: ";
			ss << (int)(mgsi->length);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += '\n';

			for(int ix = 0; ix < mgsi->count; ix++)
			{
				if(mgsi->value[ix].choice == MDS_GEN_SYSTEM_INFO_SYSTEM_PULSE_CHOSEN)
				{
					attributeContents += "\t\tMDS_GEN_SYSTEM_INFO_SYSTEM_PULSE_CHOSEN\n";
				}
				else
				{
					attributeContents += "\t\tchoice: ";
					ss << (int)(mgsi->value[ix].choice);
					attributeContents += ss.str();
					ss.str("");
					attributeContents += '\n';
				}

				attributeContents += "\t\tlength: ";
				ss << (int)(mgsi->value[ix].length);
				attributeContents += ss.str();
				ss.str("");
				attributeContents += '\n';
				attributeContents += "\t\t";

				for(int jx = 0; jx < mgsi->value[ix].length ; jx++)
				{
					ss << (int)(mgsi->value[ix].value[jx]);;
					attributeContents += ss.str();
					ss.str("");
				}
				attributeContents += '\n';
			}
		}
		break;

		case NOM_ATTR_POLL_OBJ_PRIO_NUM:
		{
			uint16_t* u16 = reinterpret_cast<uint16_t *>(dbxa.ps);
			attributeContents.clear();

			attributeContents += "\tvalue: ";
			stringstream ss;
			ss << (int)(*u16);
			attributeContents += ss.str();
			ss.str("");
			attributeContents += '\n';
		}
		break;

		case NOM_ATTR_POLL_NU_PRIO_LIST:
		{
			TextIdList* textIdList = reinterpret_cast<TextIdList *>(dbxa.ps);
			attributeContents.clear();
			attributeContents += "\tcount: ";
			stringstream ss;
			ss << (int)(textIdList->count);
			attributeContents += ss.str();
			attributeContents += '\n';
			attributeContents += "\tlength: ";
			ss.str("");
			ss << (int)(textIdList->length);
			attributeContents += ss.str();
			attributeContents += '\n';

			for(int ix = 0; ix < textIdList->count; ix++)
			{
				attributeContents += "\t\tTextID: ";
				attributeContents += TextIdName(textIdList->value[ix]);
				attributeContents += '\n';
			}
		}
		break;

		case NOM_ATTR_POLL_RTSA_PRIO_LIST:
		{
			TextIdList* textIdList = reinterpret_cast<TextIdList *>(dbxa.ps);
			attributeContents.clear();
			attributeContents += "\tcount: ";
			stringstream ss;
			ss << (int)(textIdList->count);
			attributeContents += ss.str();
			attributeContents += '\n';
			attributeContents += "\tlength: ";
			ss.str("");
			ss << (int)(textIdList->length);
			attributeContents += ss.str();
			attributeContents += '\n';

			for(int ix = 0; ix < textIdList->count; ix++)
			{
				attributeContents += "\t\tTextID: ";
				attributeContents += TextIdName(textIdList->value[ix]);
				attributeContents += '\n';
			}
		}
		break;

		case NOM_ATTR_GRP_AL_MON:
			// Not in manual
		break;

		case NOM_ATTR_GRP_METRIC_VAL_OBS:
			// Not in manual
		break;

		case NOM_ATTR_GRP_PT_DEMOG:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_APPL:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_ID:
			// Not in manual
		break;

		case NOM_ATTR_GRP_SYS_PROD:
			// Not in manual
		break;

		case NOM_ATTR_GRP_VMO_DYN:
			// Not in manual
		break;

		case NOM_ATTR_GRP_VMO_STATIC:
			// Not in manual
		break;

		default:
		break;
	}
	return attributeContents;
}
#endif
