BEGIN{
	transize=0
	recvsize=0
	start=400
	stop=0
}

{
	event=$1
	time=$3
	sender=$5
	receiver=$7
	fid=$17
	
	if(sender=="0"){
		if(start>time){
			start=time
		}
		if(fid=="1"){
			transize+=1
		}
	}
	if(receiver=="1"){
		if(stop<time){
			stop=time
		}
		if(fid=="1"){
			recvsize+=1
		}
	}		
}

END{
	printf("Packet lost: %d\n", transize-recvsize)
	printf("Throughput: %.2f \n", recvsize/(stop-start))
}
