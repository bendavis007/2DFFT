	program give_maximum_pitch_phase
	implicit none
	integer i,npts,m,nlet,i_max,radio
	real  p(5000),value(5000),modulus
	real max,p_max,pitch,phase(5000),p_real,p_imag,PI
	character keyword*80,infile1*80,infile2*80

	PI=3.1415926

	write(*,*)'keyword : '
	read(*,'(a)')keyword

	do i=1,80	
	 if(keyword(i:i).EQ.' ')then
	   nlet=i-1
	   goto 30
	  endif
	enddo

30	infile1=keyword(1:nlet)//'.dat'
	infile2=keyword(1:nlet)//'.rip'

	do i=1,80
	  if(infile1(i:i).EQ.'.')read(infile1(i-1:i-1),'(i1)')m
	enddo

	open(unit=1,file=infile1,status='old')

	i=1
10	read(1,*,end=99)p(i),value(i)
	i=i+1
	goto 10
99	close(1)
	npts=i-1

	i_max=0
	max=0.0
	p_max=100.
	do i=1,npts
	  if(value(i).GT.max)then
	    max=value(i)
	    p_max=p(i)
	    i_max=i
	  endif
	enddo

	pitch=atan2(float(-m),p_max)*180./3.1415926
	if(abs(pitch).GT.90.)pitch=180.+pitch

	open(unit=1,file=infile2,status='old')
	read(1,*)radio
	read(1,*)modulus
	do i=1,npts
	  read(1,*)p_real
	  read(1,*)p_imag
	  phase(i)=atan2(p_imag,p_real)*180/PI/m
	enddo
	
	OPEN (7, FILE = 'temp_pitch_data')
	write(7,200)m,keyword,p_max,max,pitch,phase(i_max)
200	format(I6.1,2X,A9,2X,F6.2,2X,F10.3,3X,F6.2,3X,F8.3)

	end
