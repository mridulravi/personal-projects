#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Blue

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

# Open the trace file
set f [open udp-40k.tr w]
$ns trace-all $f

#Define a 'finish' procedure
proc finish {} {
    global ns nf f
    $ns flush-trace
    #Close the NAM trace file
    close $nf
    # Close the trace file
    close $f
    #Execute NAM on the trace file
    exec nam out.nam &
    exit 0
}

#Create three nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

#Create links between the nodes
$ns duplex-link $n0 $n1 1Mb 50ms DropTail
$ns duplex-link $n1 $n2 100Kb 5ms DropTail

#Set Queue Size of link (n1-n2) to 10
$ns queue-limit $n1 $n2 10

#Give node position (for NAM)
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

#Monitor the queue for link (n1-n2). (for NAM)
$ns duplex-link-op $n1 $n2 queuePos 0.5

#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp $null
$udp set fid_ 2

#Setup a CBR over UDP connection (40 kbps = 50 bytes every 10ms)
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 50
$cbr set interval_ 0.010
$cbr set random_ false

#Start and stop CBR
$ns at 0.5 "$cbr start"
$ns at 20.5 "$cbr stop"

#Call the finish procedure after 21 seconds of simulation time
$ns at 21.0 "finish"

#Run the simulation
$ns run

