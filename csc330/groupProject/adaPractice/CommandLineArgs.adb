-- CommandLineArgs.adb

with Ada.Text_IO;
with Ada.Command_Line;

procedure CommandLineArgs is
begin
   -- Check if there are any command line arguments
   if Ada.Command_Line.Argument_Count = 0 then
      Ada.Text_IO.Put_Line("No command line arguments provided.");
   else
      -- Print each command line argument
      Ada.Text_IO.Put_Line("Command line arguments:");

      for I in 1 .. Ada.Command_Line.Argument_Count loop
         Ada.Text_IO.Put_Line("Argument " & Integer'Image(I) & ": " & Ada.Command_Line.Argument(I));
      end loop;
   end if;
end CommandLineArgs;
