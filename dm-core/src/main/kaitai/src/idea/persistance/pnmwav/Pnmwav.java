// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

package idea.persistance.pnmwav;

import io.kaitai.struct.ByteBufferKaitaiStream;
import io.kaitai.struct.KaitaiStruct;
import io.kaitai.struct.KaitaiStream;
import java.io.IOException;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;
import java.nio.charset.Charset;

public class Pnmwav extends KaitaiStruct {
    public static Pnmwav fromFile(String fileName) throws IOException {
        return new Pnmwav(new ByteBufferKaitaiStream(fileName));
    }

    public enum Filetag {
        FT_HEADER_BEGIN(5000),
        FT_HEADER_END(5001),
        FT_FILE_VERSION(5002),
        FT_CHANNEL_LIST_PTR(5003),
        FT_BLOCK_LIST_PTR(5004),
        FT_CHAN_LIST_BEGIN(5005),
        FT_CHAN_LIST_END(5006),
        FT_CHAN_BEGIN(5007),
        FT_CHAN_END(5008),
        FT_CHAN_ID_INT(5009),
        FT_DATA_BLOCK_BEGIN(5010),
        FT_DATA_BLOCK_END(5011),
        FT_TICKS_PER_SAMPLE(5012),
        FT_START_TIME(5013),
        FT_END_TIME(5014),
        FT_DATA_CHUNK(5015),
        FT_BLOCK_LIST_BEGIN(5016),
        FT_BLOCK_LIST_END(5017),
        FT_BLOCK_ENTRY_BEGIN(5018),
        FT_BLOCK_ENTRY_END(5019),
        FT_BLOCK_PTR(5020),
        FT_UNUSED3(5021),
        FT_STORAGE_INFO_BEGIN(5022),
        FT_STORAGE_INFO_TYPE(5023),
        FT_STORAGE_INFO_END(5024),
        FT_AD_LOW(5025),
        FT_AD_HIGH(5026),
        FT_UNUSED1(5027),
        FT_UNUSED2(5028),
        FT_LOWSCALE(5029),
        FT_HIGHSCALE(5030),
        FT_SUPER_INDEX_BEGIN(5031),
        FT_SUPER_SEGMENT_BEGIN(5032),
        FT_SUPER_SEGMENT_END(5033),
        FT_SUPER_INDEX_PTR(5034),
        FT_SUPER_ENTRY_BEGIN(5035),
        FT_SUPER_ENTRY_END(5036),
        FT_SUPER_INDEX_END(5037),
        FT_EARLIEST_FILE_TIME(5038),
        FT_LATEST_FILE_TIME(5039),
        FT_SUBJECT_ID_INT(5040),
        FT_SUBJECT_NAME(5041),
        FT_LOCAL_TIME_ZONE_ID(5042),
        FT_ACQ_SUCCESSFULLY_COMPLETED(5043),
        FT_SUBJECT_ID(5044),
        FT_CHANNEL_ID(5045);

        private final long id;
        Filetag(long id) { this.id = id; }
        public long id() { return id; }
        private static final Map<Long, Filetag> byId = new HashMap<Long, Filetag>(46);
        static {
            for (Filetag e : Filetag.values())
                byId.put(e.id(), e);
        }
        public static Filetag byId(long id) { return byId.get(id); }
    }

    public Pnmwav(KaitaiStream _io) {
        this(_io, null, null);
    }

    public Pnmwav(KaitaiStream _io, KaitaiStruct _parent) {
        this(_io, _parent, null);
    }

    public Pnmwav(KaitaiStream _io, KaitaiStruct _parent, Pnmwav _root) {
        super(_io);
        this._parent = _parent;
        this._root = _root == null ? this : _root;
        _read();
    }
    private void _read() {
        this.magic = this._io.ensureFixedContents(new byte[] { -81, 85, 85, -86 });
        this.header = new PnmHeader(this._io, this, _root);
        this.channelTags = new PnmTaglist(this._io, this, _root);
    }
    public static class PnmChannelPtr extends KaitaiStruct {
        public static PnmChannelPtr fromFile(String fileName) throws IOException {
            return new PnmChannelPtr(new ByteBufferKaitaiStream(fileName));
        }

        public PnmChannelPtr(KaitaiStream _io) {
            this(_io, null, null);
        }

        public PnmChannelPtr(KaitaiStream _io, KaitaiStruct _parent) {
            this(_io, _parent, null);
        }

        public PnmChannelPtr(KaitaiStream _io, KaitaiStruct _parent, Pnmwav _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.channelDescOffset = this._io.readU8le();
        }
        private byte[] channelList;
        public byte[] channelList() {
            if (this.channelList != null)
                return this.channelList;
            long _pos = this._io.pos();
            this._io.seek(channelDescOffset());
            this.channelList = this._io.readBytes(100);
            this._io.seek(_pos);
            return this.channelList;
        }
        private long channelDescOffset;
        private Pnmwav _root;
        private KaitaiStruct _parent;
        public long channelDescOffset() { return channelDescOffset; }
        public Pnmwav _root() { return _root; }
        public KaitaiStruct _parent() { return _parent; }
    }
    public static class PnmDatachunk extends KaitaiStruct {
        public static PnmDatachunk fromFile(String fileName) throws IOException {
            return new PnmDatachunk(new ByteBufferKaitaiStream(fileName));
        }

        public PnmDatachunk(KaitaiStream _io) {
            this(_io, null, null);
        }

        public PnmDatachunk(KaitaiStream _io, Pnmwav.PnmTag _parent) {
            this(_io, _parent, null);
        }

        public PnmDatachunk(KaitaiStream _io, Pnmwav.PnmTag _parent, Pnmwav _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.v = new ArrayList<Short>();
            {
                int i = 0;
                while (!this._io.isEof()) {
                    this.v.add(this._io.readS2le());
                    i++;
                }
            }
        }
        private ArrayList<Short> v;
        private Pnmwav _root;
        private Pnmwav.PnmTag _parent;
        public ArrayList<Short> v() { return v; }
        public Pnmwav _root() { return _root; }
        public Pnmwav.PnmTag _parent() { return _parent; }
    }
    public static class PnmTaglist extends KaitaiStruct {
        public static PnmTaglist fromFile(String fileName) throws IOException {
            return new PnmTaglist(new ByteBufferKaitaiStream(fileName));
        }

        public PnmTaglist(KaitaiStream _io) {
            this(_io, null, null);
        }

        public PnmTaglist(KaitaiStream _io, KaitaiStruct _parent) {
            this(_io, _parent, null);
        }

        public PnmTaglist(KaitaiStream _io, KaitaiStruct _parent, Pnmwav _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.tags = new ArrayList<PnmTag>();
            {
                int i = 0;
                while (!this._io.isEof()) {
                    this.tags.add(new PnmTag(this._io, this, _root));
                    i++;
                }
            }
        }
        private ArrayList<PnmTag> tags;
        private Pnmwav _root;
        private KaitaiStruct _parent;
        public ArrayList<PnmTag> tags() { return tags; }
        public Pnmwav _root() { return _root; }
        public KaitaiStruct _parent() { return _parent; }
    }
    public static class PnmHeader extends KaitaiStruct {
        public static PnmHeader fromFile(String fileName) throws IOException {
            return new PnmHeader(new ByteBufferKaitaiStream(fileName));
        }

        public PnmHeader(KaitaiStream _io) {
            this(_io, null, null);
        }

        public PnmHeader(KaitaiStream _io, Pnmwav _parent) {
            this(_io, _parent, null);
        }

        public PnmHeader(KaitaiStream _io, Pnmwav _parent, Pnmwav _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.headerStart = this._io.ensureFixedContents(new byte[] { -120, 19 });
            this.headerLen = this._io.readU4le();
            this.headerEnd = this._io.readU8le();
            this._raw_headerPayload = this._io.readBytes((headerEnd() - _io().pos()));
            KaitaiStream _io__raw_headerPayload = new ByteBufferKaitaiStream(_raw_headerPayload);
            this.headerPayload = new PnmTaglist(_io__raw_headerPayload, this, _root);
        }
        private byte[] headerStart;
        private long headerLen;
        private long headerEnd;
        private PnmTaglist headerPayload;
        private Pnmwav _root;
        private Pnmwav _parent;
        private byte[] _raw_headerPayload;
        public byte[] headerStart() { return headerStart; }
        public long headerLen() { return headerLen; }
        public long headerEnd() { return headerEnd; }
        public PnmTaglist headerPayload() { return headerPayload; }
        public Pnmwav _root() { return _root; }
        public Pnmwav _parent() { return _parent; }
        public byte[] _raw_headerPayload() { return _raw_headerPayload; }
    }
    public static class PnmTag extends KaitaiStruct {
        public static PnmTag fromFile(String fileName) throws IOException {
            return new PnmTag(new ByteBufferKaitaiStream(fileName));
        }

        public PnmTag(KaitaiStream _io) {
            this(_io, null, null);
        }

        public PnmTag(KaitaiStream _io, Pnmwav.PnmTaglist _parent) {
            this(_io, _parent, null);
        }

        public PnmTag(KaitaiStream _io, Pnmwav.PnmTaglist _parent, Pnmwav _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.tagId = Pnmwav.Filetag.byId(this._io.readU2le());
            this.tagLen = this._io.readU4le();
            switch (tagId()) {
            case FT_BLOCK_LIST_PTR: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_HIGHSCALE: {
                this.payload = (Object) (this._io.readF4le());
                break;
            }
            case FT_SUBJECT_ID: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_SUPER_INDEX_PTR: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_DATA_CHUNK: {
                this._raw_payload = this._io.readBytes(tagLen());
                KaitaiStream _io__raw_payload = new ByteBufferKaitaiStream(_raw_payload);
                this.payload = new PnmDatachunk(_io__raw_payload, this, _root);
                break;
            }
            case FT_STORAGE_INFO_BEGIN: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_START_TIME: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_EARLIEST_FILE_TIME: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_SUBJECT_ID_INT: {
                this.payload = (Object) (this._io.readU4le());
                break;
            }
            case FT_END_TIME: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_SUBJECT_NAME: {
                this.payload = new String(this._io.readBytes(tagLen()), Charset.forName("utf-8"));
                break;
            }
            case FT_TICKS_PER_SAMPLE: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_CHAN_BEGIN: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_BLOCK_PTR: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_FILE_VERSION: {
                this.payload = (Object) (this._io.readU4le());
                break;
            }
            case FT_CHANNEL_ID: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_ACQ_SUCCESSFULLY_COMPLETED: {
                this.payload = (Object) (this._io.readU4le());
                break;
            }
            case FT_LOCAL_TIME_ZONE_ID: {
                this.payload = new String(this._io.readBytes(tagLen()), Charset.forName("utf-8"));
                break;
            }
            case FT_LATEST_FILE_TIME: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_AD_LOW: {
                this.payload = (Object) (this._io.readS2le());
                break;
            }
            case FT_STORAGE_INFO_TYPE: {
                this.payload = (Object) (this._io.readU4le());
                break;
            }
            case FT_DATA_BLOCK_BEGIN: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_AD_HIGH: {
                this.payload = (Object) (this._io.readS2le());
                break;
            }
            case FT_BLOCK_ENTRY_BEGIN: {
                this.payload = (Object) (this._io.readU8le());
                break;
            }
            case FT_LOWSCALE: {
                this.payload = (Object) (this._io.readF4le());
                break;
            }
            default: {
                this.payload = this._io.readBytes(tagLen());
                break;
            }
            }
        }
        private Filetag tagId;
        private long tagLen;
        private Object payload;
        private Pnmwav _root;
        private Pnmwav.PnmTaglist _parent;
        private byte[] _raw_payload;
        public Filetag tagId() { return tagId; }
        public long tagLen() { return tagLen; }
        public Object payload() { return payload; }
        public Pnmwav _root() { return _root; }
        public Pnmwav.PnmTaglist _parent() { return _parent; }
        public byte[] _raw_payload() { return _raw_payload; }
    }
    private byte[] magic;
    private PnmHeader header;
    private PnmTaglist channelTags;
    private Pnmwav _root;
    private KaitaiStruct _parent;
    public byte[] magic() { return magic; }
    public PnmHeader header() { return header; }
    public PnmTaglist channelTags() { return channelTags; }
    public Pnmwav _root() { return _root; }
    public KaitaiStruct _parent() { return _parent; }
}
