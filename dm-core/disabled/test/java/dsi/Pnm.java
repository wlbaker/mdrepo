package dsi;

public class Pnm {
	enum Tag
     {
             Unknown( 0 ),

             HeaderBegin( 5000 ), // file location (8 bytes)
             HeaderEnd(5001),          // null (0 bytes)
             FileVersion(5002),        // int (4 bytes)
             ChannelListPtr(5003),     // file location (8 bytes)
             BlockListPtr(5004),       // file location (8 bytes)

             ChanListBegin(5005),      // file location (8 bytes)
             ChanListEnd(5006),        // null (0 bytes)
             ChannelBegin(5007),       // file location (8 bytes)
             ChannelEnd(5008),         // null (0 bytes)
             ChannelIdInt(5009),       // int (4 bytes) - used in 6.0, preserved for file reading only

             DataBlockBegin(5010),     // file location (8 bytes)
             DataBlockEnd(5011),       // null (0 bytes)
             TicksPerSample(5012),     // ticks (8 bytes)
             StartTime(5013),          // ticks (8 bytes)
             EndTime(5014),            // ticks (8 bytes)
             DataChunk(5015),          // big (many bytes)

             BlockListBegin(5016),     // file location (8 bytes)
             BlockListEnd(5017),       // null (0 bytes)
             BlockEntryBegin(5018),    // file location (8 bytes)
             BlockEntryEnd(5019),      // null (0 bytes)
             BlockPtr(5020),           // file location (8 bytes)

             Unused3(5021),            // ---

             StorageInfoBegin(5022),   // file location (8 bytes)
             StorageInfoType(5023),    // int (4 bytes)
             StorageInfoEnd(5024),     // null (0 bytes)

             AdLow(5025),              // short (2 bytes)
             AdHigh(5026),             // short (2 bytes)
             Unused1(5027),            // ---
             Unused2(5028),            // ---
             LowScale(5029),           // float (4 bytes)
             HighScale(5030),          // float (4 bytes)

             SuperIndexBegin(5031),    // file location (8 bytes)
             SuperSegmentBegin(5032),  // file location (8 bytes)
             SuperSegmentEnd(5033),    // null (0 bytes)
             SuperIndexPtr(5034),      // file location (8 bytes)
             SuperEntryBegin(5035),    // null (0 bytes)
             SuperEntryEnd(5036),      // null (0 bytes)
             SuperIndexEnd(5037),      // null (0 bytes)

             EarliestFileTime(5038),   // ticks (8 bytes)
             LatestFileTime(5039),     // ticks (8 bytes)
             SubjectIdInt(5040),       // int (4 bytes) - used in 6.0, preserved for file reading only
             SubjectName(5041),        // string (variable)
             LocalTimeZoneID(5042),    //string (variable)
             AcqSuccessfullyCompleted(5043),       //int (4 bytes)
             SubjectId(5044),          // long (8 bytes)
             ChannelId(5045);                       // long (8 bytes)
		
			private int val;
			private Tag( int v ) {
				val = v;
			}
			public int val() {
				return val;
			}
     }
}
