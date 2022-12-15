set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam
	exit 0 
}


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right


$ns queue-limit $n0 $n1 2

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp

set null [new Agent/Null]
$ns attach-agent $n1 $null

$ns connect $udp $null

set cbr1 [new Application/Traffic/CBR]
$udp set packetSize_ 500
$udp set window_ 650
$udp set fid_ 1

$cbr1 attach-agent $udp

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n1 $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink

$ns connect $tcp $sink

$tcp set packetSize_ 1000
$tcp set window_ 65000
$tcp set fid_ 2

set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $tcp

$ns at 0.1 "$cbr1 start"
$ns at 0.1 "$cbr2 start"
$ns at 4.5 "$cbr1 stop"
$ns at 4.5 "$cbr2 stop"
$ns at 4.5 "$ns detach-agent $n0 $tcp; $ns detach-agent $n2 $sink"
$ns at 5.0 "finish"

$ns run

