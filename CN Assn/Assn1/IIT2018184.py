from mininet.topo import Topo
from mininet.util import irange
 
class topology( Topo ): 
    def build( self ):
        self.racks = []
        rootSw = self.addSwitch( 's1' )
        for i in irange( 1, 4 ):
            rack = self.buildRack( i )
            self.racks.append( rack )
            for switch in rack:
                self.addLink( rootSw, switch )
 
    def buildRack( self, loc ):
        dpid = ( loc * 16 ) + 1
        switch = self.addSwitch( 'Sw1_c%s' % loc, dpid='%x' % dpid )
        for n in irange( 1, 4 ):
            host = self.addHost( 'PC%sc%s' % ( n, loc ) )
            self.addLink( switch, host )
        return [switch] 
topos = {
    'topobasic': topology
}

# ryu-manager ryu.app.simple_switch_13 ryu.app.ofctl_rest
# sudo mn --custom IIT2018184.py --topo topobasic --mac --switch ovs --controller remote