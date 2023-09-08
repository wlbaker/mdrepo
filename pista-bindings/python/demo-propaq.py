
import pypistax
import json
import sys

class MyHandler(pypistax.PistaEventHandler):

    def __init__(self):
        pypistax.PistaEventHandler.__init__(self)

    def dump_field( self, p, idx ):

        subtyp = p.getFieldSubtyp(idx)
        tot = p.getFieldQuantifier(idx)
        loc = p.getDescriptorLoc(idx) 
        # try:
        tm = p.getTm() 
        arr = None
        val = None
        print( '{0} {1} [{2:2d},{3:2d}]: '.format(loc, idx, tot, subtyp), end='' )
        if subtyp == pypistax.INT_TYP:
            val = p.getInt(idx)
        elif subtyp == pypistax.LONG_TYP:
            val = p.getLong(idx)
        elif subtyp == pypistax.FLOAT_TYP:
            val = p.getFloat(idx)
        elif subtyp == pypistax.DOUBLE_TYP:
            val = p.getDouble(idx)
        elif subtyp == pypistax.INT_ARR_TYP:
            arr = p.getIntArray(idx)
        elif subtyp == pypistax.FLOAT_ARR_TYP:
            arr = p.getFloatArray(idx)
        elif subtyp == pypistax.DOUBLE_ARR_TYP:
            arr = p.getDoubleArray(idx)

        if not val is None:
            print("field val: " + str(val), end='')
        elif arr is None:
            print("no data?", end='')
        else:
            for ii in range(0, tot ):
                print( '{0:.3f}, '.format((arr[ii]) ), end='' )
        print()

    def event(self, dev, packet):
        global p
        p = packet
        tot = packet.getDescriptorCount()
        print("Packet received: " + str(packet.getStreamID()) + "/" + str(tot) )
        for idx in range(0, tot ):
            try:
                self.dump_field( packet, idx )
            except:
                e = sys.exc_info()[0] 
                print( "Error in try: " + str(idx) + "=" + str(e) )

        return 0

ver = pypistax.getPistaVersion()
pista = pypistax.PistaCl_getInstance()

print( "** Welcome to Python Pista Demo" )
print()
print( "> Pista Version: " + pypistax.getPistaVersion() )
print( "> " + str(pista.driver_count()) + " Devices compled into PISTA:" )

for i in range(0, pista.driver_count() ):
    d1 = pista.driver(i)
    print( "  " + str(i) + " ", end='' )
    print( d1.longname() )


print()
# print( "Device selection: ", end='' )
sel = input( "Device selection: " )

driver = pista.driver( int(sel) )
print( sel + " " + str(driver) )

propaq = driver.allocate()
propaq.setOption("host","192.168.50.100")
propaq.setOption("user","zolldata:MDARK2018")

propaq.setOption("wss","false")

propaq.dump( pypistax.PISTA_DUMP_CONFIG )
propaq.dump( pypistax.PISTA_DUMP_STREAMS )

# propaq.connect()

# fname = '../../../doc/trace/propaqm-numerics-data'
# with open( fname, 'r') as myfile:
  # data = myfile.read()

# parsed = json.loads(data)
# print( json.dumps(parsed, indent=4, sort_keys=True) )
# propaq.handle( data, len(data) )



handler = MyHandler()

print()
print( "** Asynchronous test" )
print()

propaq.attach( handler.__disown__() )
propaq.connect()

input("Press ENTER to stop...\n")

propaq.disconnect()

