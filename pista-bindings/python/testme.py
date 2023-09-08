
from pypistax import *


class clpkt():
    __swig_setmethods__ = {}
    # __setattr__ = lambda self, name, value: _swig_setattr(self, PistaDataPacket, name, value)
    __swig_getmethods__ = {}
    # __getattr__ = lambda self, name: _swig_getattr(self, PistaDataPacket, name)
    # __repr__ = _swig_repr

    def __init__(self, pkt: 'pista_data_packet'):
        print( "initted self" )
        this = 0 # _pypistax.new_PistaDataPacket(pkt)
        #try:
            #self.this.append(this)
        #except __builtin__.Exception:
            #self.this = this
        self.this = this

    def getTm(self):
        return _pypistax.PistaDataPacket_getTm(self)

    def getTm0(self, desc_idx: 'int') -> "char const *":
        return _pypistax.PistaDataPacket_getDescriptorLoc(self, desc_idx )

    def getTm2(self) -> "int64_t":
        print("getting tm2\n"); 
        return 0


ver = getPistaVersion()
print(ver)
tm = pista_get_current_time_with_ms()
print(tm)

cpkt = pista_data_packet( )

pkt = clpkt( cpkt )
tm2 = pkt.getTm2()
print("tm2=" + str(tm2) )

