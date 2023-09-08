
import pypistax
import sys 

p = None

class MyHandler(pypistax.PistaEventHandler):

    def __init__(self):
        pypistax.PistaEventHandler.__init__(self)

    def dump_packet( self, p, idx ):

        subtyp = p.getFieldSubtyp(idx)
        tot = p.getFieldQuantifier(idx)
        loc = p.getDescriptorLoc(idx) 
        # try:
        tm = p.getTm() 
        val = None
        arr = None
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
        p = packet  # this packet is actually the payload, and may be none
        # unfortunately, I've stripped off the SID and I'm not passing it in to the callback!
        # here I should have
        # packet = event.getPayload()
        if not packet is None:
            tot = packet.getDescriptorCount()
            print("Packet received: " + str(packet.getStreamID()) + "/" + str(tot) )
            for idx in range(0, tot ):
                self.dump_packet( packet, idx )

        return 0

def devselection():

    print( "> " + str(pista.driver_count()) + " Devices compled into PISTA:" )
    print()

    for i in range(0, pista.driver_count() ):
        d1 = pista.driver(i)
        print( "  " + str(i) + " " + d1.longname() )

    print()
    sel = input( "Device selection: " )
    print()

    return sel

def sync_test( simu, handler ):
    pkt = simu.poll( ord('M') )

    pkt = simu.poll( ord('W') )
    tot = pkt.getDescriptorCount()
    print("Packet polled: " + str(pkt.getStreamID()) + "/" + str(tot) )
    for idx in range(0, tot ):
        handler.dump_packet( pkt, idx )


print( "** Welcome to Python Pista SIMU Demo" )
print( "> Pista Version: " + pypistax.getPistaVersion() )
print()

pista = pypistax.PistaCl_getInstance()

sel = devselection()
driver = pista.driver( int(sel) )
print( str(sel) + " " + str(driver) )

simu = driver.allocate()

handler = MyHandler()

print( "** Synchronous test" )
print()

sync_test( simu, handler )

input("Press ENTER to continue...\n")
print()
print( "** Asynchronous test" )
print()
# simu.dump( pypistax.PISTA_DUMP_CONFIG )
# simu.dump( pypistax.PISTA_DUMP_STREAMS )


simu.attach( handler.__disown__() )
simu.connect()

input("Press ENTER to stop...\n")

simu.disconnect()

print("Simu DISCONNECT complete")
