#importonce
.print "Plus/4 BASIC header"
	* = $1001

{
	.word basend
	.word 2021
	.byte $9e	// BASIC SYS token
	.text "4109"
	.byte 0
basend:	.word 0
}