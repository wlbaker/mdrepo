package idea.driver.intellivue;

import static idea.driver.intellivue.C.NOM_ACT_POLL_MDIB_DATA;
import static idea.driver.intellivue.C.NOM_ACT_POLL_MDIB_DATA_EXT;
import static idea.driver.intellivue.C.NOM_MOC_VMS_MDS;

import java.nio.ByteBuffer;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@Data
public class ActionResult implements Reportable {

	private short actionType;
	private SingleContextPoll[] polls;
	private ManagedObjectID objectID;

	public static ActionResult parse(ByteBuffer bb, int invoke_id) {
		ActionResult res = new ActionResult();

		
		int scope = -1;
		res.objectID = ManagedObjectID.parse(bb);
		//		if (invoke_id < 64) {
		//			scope = bb.getInt();
		//		}

		res.actionType = bb.getShort(); // OIDType u_16
		short action_len = bb.getShort();

		assert (res.objectID.object_class == NOM_MOC_VMS_MDS) : "[IntellivueDriver] expecting NOM_MOC_VMS_MDS";
		// NOM_ACT_POLL_MDIB_DATA used for single poll data request
		// NOM_ACT_POLL_MDIB_DATA_EXT used for extended poll data request

		switch (res.actionType) {

		case NOM_ACT_POLL_MDIB_DATA:
			res.polls = parsePollMdibDataReply(bb);
			break;
		case NOM_ACT_POLL_MDIB_DATA_EXT:
			res.polls = parsePollMdibDataReplyExt(bb);
			break;
		default:
			log.error("parse action result unknown: invoke_id ={} type={}", invoke_id, res.actionType);
		}

		return res;
	}

	private static SingleContextPoll[] parsePollMdibDataReply(ByteBuffer bb) {
		short poll_number = bb.getShort();
		return _parsePolledMdibDataReplyX(poll_number, bb);
	}

	private static SingleContextPoll[] parsePollMdibDataReplyExt(ByteBuffer bb) {
		short poll_number = bb.getShort();
		short seq_no = bb.getShort();
		return _parsePolledMdibDataReplyX(poll_number, bb);
	}

	private static SingleContextPoll[] _parsePolledMdibDataReplyX(short poll_no, ByteBuffer bb) {

		int rel_ts = bb.getInt();
		long abs_ts = IntellivueUtil.parseAbsTimeStamp(bb);

		short partition = bb.getShort();
		short code = bb.getShort();
		
		//		if (code == NOM_MOC_VMO_METRIC_SA_RT) {
		//			System.out.println("GOT WAVEFORM!!!!!!!!!!!");
		//		}
		short polled_attr_group = bb.getShort();

		SingleContextPoll[] polls = null;
		switch (partition) {
		case C.NOM_PART_OBJ:
			polls = parsePollInfoList(polled_attr_group, bb);
			break;
		case C.NOM_PART_PGRP:
			log.error("I GOT A NON-OBJECT!!!! PGRP???");
			break;
		default:
			log.error("I GOT A NON-OBJECT!!!! -- MAYBE PHYSIOLOGICAL OR ALARM?");
		}

		return polls;
	}

	private static SingleContextPoll[] parsePollInfoList(short polled_attr_group, ByteBuffer bb) {
		// PollInfoList

		short count = bb.getShort();
		short length = bb.getShort();
		int pos1 = bb.position();

		SingleContextPoll[] polls = null;
		if (count > 0) {
			polls = new SingleContextPoll[count];
			for (int i = 0; i < count; i++) {
				polls[i] = SingleContextPoll.parse(bb);
			}
		}
		int pos2 = bb.position();
		assert (length == pos2 - pos1) : "[parsePollInfoList] length mismatch: " + length + " != " + (pos2 - pos1);

		return polls;
	}

	@Override
	public void dump() {
		System.out.println("ACTION RESULT");

		objectID.dump();
		if (polls == null) {
			System.out.println("NO POLLS!");
		} else {
			for (SingleContextPoll poll : polls) {
				poll.dump();
			}
		}
	}

}

