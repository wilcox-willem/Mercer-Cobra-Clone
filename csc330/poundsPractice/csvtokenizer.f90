program parse 

    character(:), allocatable :: line, outline, word

    interface
        subroutine get_next_token( inline, outline, word)
                character (*) :: inline
                character(:), allocatable :: outline, word
        end subroutine get_next_token 
    end interface

    line = "10H, AD, 8C, 7C, 5H"
    print *, line
    print *, "The length of the string is ", len(line)

    ! Initialize outline to be same string as line, it will get overwritten in 
    ! the subroutine, but we need it for loop control

    outline = line


    do while (len(outline) .ne. 0)
        call get_next_token( line, outline, word)
        print *, word
        line = outline
    enddo

end program parse 

subroutine get_next_token( inline, outline, token)

        character (*) :: inline
        character(:), allocatable :: outline, token 
        integer :: i, j
        logical :: foundFirst, foundLast

        ! Initialize variables used to control loop

        foundFirst = .false.
        foundLast  = .false.
        i = 0


        ! find first comma 
        do while ( .not. foundFirst .and. (i < len(inline)))  
            if (inline(i:i) .eq. ",") then
                i = i + 1
            else
                foundFirst = .true.
            endif
        enddo

        j = i
        do while ( foundFirst .and. .not. foundLast .and. ( j < len(inline)))
            if (inline(j:j) .ne. ",") then
                j = j + 1
            else
                foundLast = .true.
            endif
        enddo

! WW: Changes made
!previous version
  ! token = trim(inline(i:j))
  ! outline = trim(inline(j+1:len(inline)))
!New version below, checks if foundFirst or foundLast, to handle if last item or not


        if (.not. foundLast) then
          token = trim(inline(i:j))
          outline = trim(inline(j+2:len(inline)))
        else  
          token = trim(inline(i:j -1)) !the (i:j -1) removes comma from first 4 items
          outline = trim(inline(j+2:len(inline)))
        endif


end subroutine get_next_token  
