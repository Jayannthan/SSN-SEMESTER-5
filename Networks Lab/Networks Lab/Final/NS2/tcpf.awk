BEGIN{
	sentpackets=0
	rcvdpackets=0
	start=999
	end=0
}
{
	event=$1
	time=$3
	sender=$5
	xrvr=$7
	flow=$17

	if(sender=="0")
	{
		if(event=="+")
		{
			if(start>time)
			{
				start=time
			}
			sentpackets=sentpackets+1
		}
	}

	if(xrvr=="5")
	{
		if(event=="r")
		{
			if(end<time)
			{
				end=time
			}
			rcvdpackets=rcvdpackets+1
		}
	}
}

END{

	printf("\nSent=%d\nRcvd=%d\n",sentpackets,rcvdpackets)
	printf("\nThroughput=%.2f\n",rcvdpackets/(end-start))
}