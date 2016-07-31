--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:33:26 03/15/2013
-- Design Name:   
-- Module Name:   F:/Courses/CS288/VHDL/Project1/BitwiseOperations_tb.vhd
-- Project Name:  Project1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: BitwiseOperations
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
use IEEE.std_logic_arith.all;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY BitwiseOperations_tb IS
END BitwiseOperations_tb;
 
ARCHITECTURE behavior OF BitwiseOperations_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT BitwiseOperations
    PORT(
         a : IN  std_logic_vector(3 downto 0);
         b : IN  std_logic_vector(3 downto 0);
         bitwise_and : OUT  std_logic_vector(3 downto 0);
         bitwise_or : OUT  std_logic_vector(3 downto 0);
         bitwise_xor : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal a : std_logic_vector(3 downto 0) := (others => '0');
   signal b : std_logic_vector(3 downto 0) := (others => '0');

 	--Outputs
   signal bitwise_and : std_logic_vector(3 downto 0);
   signal bitwise_or : std_logic_vector(3 downto 0);
   signal bitwise_xor : std_logic_vector(3 downto 0);
 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: BitwiseOperations PORT MAP (
          a => a,
          b => b,
          bitwise_and => bitwise_and,
          bitwise_or => bitwise_or,
          bitwise_xor => bitwise_xor
        );
 

   -- Stimulus process
   stim_proc: process
		variable err_cnt: integer :=0;
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

		--! Initial values of a and b
		a <= "0000";
		b <= "0000";
		
		--! Loop for varying 'a'
		for i in 0 to 15 loop
			
			--! Loop for varying 'b'
			for j in 0 to 15 loop
				
				wait for 10 ns;
				
				--! If correct values are not found, show error
				assert((bitwise_and= (a and b) ) and (bitwise_or= (a or b )) and (bitwise_xor= (a xor b )))  report "Error Detected!"
				severity error;
				
				--!In case of wrong values, increment error count
				if ((bitwise_and/=(a and b)) or (bitwise_or/=(a or b)) or (bitwise_xor/= (a xor b))) then
					err_cnt:=err_cnt+1;
				end if;
			
				
				--! Increment value of 'b'
				b <= b + "0001";
			end loop;

			--! Increment value of 'a'
			a <= a+"0001";
		end loop;
				

		-- summary of all the tests
		if (err_cnt=0) then
			assert false
			report "Testbench of BitwiseOperations completed successfully!"
			severity note;
		else
			assert true
			report "Something wrong, try again"
			severity error;
		end if;

      wait;
   end process;

END;
