package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DeviceAlertCondition implements Reportable {

	public static final int AL_INHIBITED = 0x8000;
	public static final int AL_SUSPENDED = 0x4000;
	public static final int AL_LATCHED = 0x2000;
	public static final short AL_SILENCED_RESET = 0x1000;
	public static final short AL_DEV_IN_TEST_MODE = 0x0400;
	public static final short AL_DEV_IN_STANDBY = 0x0200;
	public static final short AL_DEV_IN_DEMO_MODE = 0x0100;
	public static final short AL_NEW_ALERT = 0x0008;
	
	private short device_alert_state;
	private short al_stat_chg_cnt;
	private short max_p_alarm;
	private short max_t_alarm;
	private short max_aud_alarm;

	private DeviceAlertCondition() { }
	
	public static DeviceAlertCondition parse(ByteBuffer bb) {
		DeviceAlertCondition cond = new DeviceAlertCondition();
		cond.device_alert_state = bb.getShort();
		cond.al_stat_chg_cnt = bb.getShort();
		cond.max_p_alarm = bb.getShort();
		cond.max_t_alarm = bb.getShort();
		cond.max_aud_alarm = bb.getShort();
		return cond;
	}

	@Override
	public void dump() {
		System.out.println( "   alert dump:");
		System.out.println( " device_alert_state: 0x" + Integer.toHexString(device_alert_state) );
		System.out.println( "    al_stat_chg_cnt: " + al_stat_chg_cnt);
		System.out.println( "        max_p_alarm: " + max_p_alarm);
		System.out.println( "        max_t_alarm: " + max_t_alarm);
		System.out.println( "      max_aud_alarm: " + max_aud_alarm);
		
		if( (device_alert_state & AL_INHIBITED) != 0 ) {
			System.out.print("AL_INHIBITED.");
		}
		if( (device_alert_state & AL_SUSPENDED) != 0 ) {
			System.out.print("AL_SUSPENDED.");
		}
		if( (device_alert_state & AL_LATCHED) != 0 ) {
			System.out.print("AL_LATCHED.");
		}
		if( (device_alert_state & AL_SILENCED_RESET) != 0 ) {
			System.out.print("AL_SILENCED_RESET.");
		}
		if( (device_alert_state & AL_DEV_IN_TEST_MODE) != 0 ) {
			System.out.print("AL_DEV_IN_TEST_MODE.");
		}
		if( (device_alert_state & AL_DEV_IN_STANDBY) != 0 ) {
			System.out.print("AL_DEV_IN_STANDBY.");
		}
		if( (device_alert_state & AL_DEV_IN_DEMO_MODE) != 0 ) {
			System.out.print("AL_DEV_IN_DEMO_MODE.");
		}
		if( (device_alert_state & AL_NEW_ALERT) != 0 ) {
			System.out.print("AL_NEW_ALERT.");
		}
		System.out.println();
	}

}
