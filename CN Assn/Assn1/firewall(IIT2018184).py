# rename the file to firewall.py

from pox.core import core
import pox.openflow.libopenflow_01 as of
from pox.lib.revent import *
from pox.lib.addresses import EthAddr

rules = [['00:00:00:00:00:01','00:00:00:00:00:05'],['00:00:00:00:00:01', '00:00:00:00:00:09'],['00:00:00:00:00:01','00:00:00:00:00:0d'],['00:00:00:00:00:02','00:00:00:00:00:06'],['00:00:00:00:00:02','00:00:00:00:00:0a'],['00:00:00:00:00:02','00:00:00:00:00:0e'],['00:00:00:00:00:03','00:00:00:00:00:07'],['00:00:00:00:00:03','00:00:00:00:00:0b'],['00:00:00:00:00:03','00:00:00:00:00:0f'],['00:00:00:00:00:04','00:00:00:00:00:08'],['00:00:00:00:00:04','00:00:00:00:00:0c'],['00:00:00:00:00:04','00:00:00:00:00:10'],['00:00:00:00:00:05','00:00:00:00:00:09'],['00:00:00:00:00:05','00:00:00:00:00:0d'],['00:00:00:00:00:09','00:00:00:00:00:0d'],['00:00:00:00:00:06','00:00:00:00:00:0a'],['00:00:00:00:00:06','00:00:00:00:00:0e'],['00:00:00:00:00:0a','00:00:00:00:00:0e'],['00:00:00:00:00:07','00:00:00:00:00:0b'],['00:00:00:00:00:07','00:00:00:00:00:0f'],['00:00:00:00:00:0b','00:00:00:00:00:0f'],['00:00:00:00:00:08','00:00:00:00:00:0c'],['00:00:00:00:00:08','00:00:00:00:00:10'],['00:00:00:00:00:0c','00:00:00:00:00:10']]

class SDNFirewall (EventMixin):
    
    def __init__ (self):
        self.listenTo(core.openflow)
        
    def _handle_ConnectionUp (self, event):
        for rule in rules:
            block = of.ofp_match()
            block.dl_src = EthAddr(rule[0])
            block.dl_dst = EthAddr(rule[1])
            flow_mod = of.ofp_flow_mod()
            flow_mod.match = block
            event.connection.send(flow_mod)
        
def launch ():
    core.registerNew(SDNFirewall)



# ./pox.py log.level --DEBUG openflow.of_01 forwarding.l2_learning misc.firewall
#  sudo mn --custom demo.py --topo dcbasic --mac --switch ovs --controller remote