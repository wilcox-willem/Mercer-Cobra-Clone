program readtest

    character(19) :: lineOfText
    character(len=*), parameter :: filename="testhands"
    character(len=*), parameter :: path="/pub/pounds/CSC330/poker/"
    character(:), allocatable :: fullpath
    integer :: io
    ! Concatenate the path and filename together
    fullpath = path // filename

    
    open(unit=5,file=fullpath,status="old")
    do
      read (5,"(a19)",iostat=io) lineOfText
      if (io/=0) exit
      print *, lineOfText
    end do

    close(5)

end program readtest
