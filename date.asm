global main

extern gettimeofday
extern strftime
extern localtime_r
extern puts

struc tv
	tv_sec resd 1
	tv_usec resd 1
endstruc

struc tz
	tz_minuteswest resd 1
	tz_dsttime resd 1
endstruc

struc tm
	tm_sec resd 1
	tm_min resd 1
	tm_hour resd 1
	tm_mday resd 1
	tm_mon resd 1
	tm_year resd 1
	tm_wday resd 1
	tm_yday resd 1
	tm_isdst resd 1
endstruc

%define OUTBUFSIZ 100h

section .bss
	timeval resb tv_size
	timezone resb tz_size
	the_time resb tm_size
	outbuf resb OUTBUFSIZ

section .data
	the_format db `%H:%M:%S %d/%m/%G`, 0

section .text
main:
	push timezone
	push timeval
	call gettimeofday
	add esp, 4 * 2

	push the_time
	push timeval
	call localtime_r
	add esp, 4 * 2

	push the_time
	push the_format
	push OUTBUFSIZ
	push outbuf
	call strftime
	add esp, 4 * 4

	push outbuf
	call puts
	add esp, 4 * 1

	ret