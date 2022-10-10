DATAS SEGMENT
	n1    db     5h
	n2    db     5h

	      CODES
	      ASSUME CS:CODES,DS:DATAS

	START:
	      MOV    AX n1
	      MOV    BX n2
	      ADD    AX,BX

CODES ENDS
END START