set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish{} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

set n(0) [$ns node]
set n(1) [$ns node]
set n(2) [$ns node]
set n(3) [$ns node]
set n(4) [$ns node]
set n(5) [$ns node]

$ns duplex-link $n(0) $n(1) 10Mb 10ms DropTail
$ns duplex-link $n(2) $n(1) 10Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 10Mb 10ms DropTail
$ns duplex-link $n(3) $n(4) 10Mb 10ms DropTail
$ns duplex-link $n(4) $n(5) 10Mb 10ms DropTail

$ns queue-limit $n(0) $n(1) 10

$ns duplex-link-op $n(0) $n(1) orient right

set tcp[new Agent/TCP]
$ns attach-agent $n(0) $tcp

set sink[new Agent/TCPSink]
$ns attach-agent $n(0) $sink

$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp set type_ FTP
$ftp attach-agent $tcp

set udp [new Agent/UDP]
$ns attach-agent $n(0) $udp

set null [new Agent/NULL]
$ns attach-agent $n(0) $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
# $cbr set packetSize_ 500
# $cbr set interval_ 0.001ms
# $cbr set rate_ 1mb
$cbr attach-agent $tcp

$ns rtproto DV
$ns rtproto LS
$ns rtmodel-at 1.0 down $n(1)  $n(3)
$ns rtmodel-at 1.5 up $n(1)  $n(3)

$ns at 0.1 "$cbr start"
$ns at 0.2 "$ftp start"
$ns at 4.5 "$cbr stop"
$ns at 4.5 "$ftp stop"


# $ns at 4.5 "$ns detach-agent $  $  ;........."

$ns at 5.0 "finish"
$ns run

