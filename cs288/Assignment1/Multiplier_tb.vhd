--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:34:05 03/15/2013
-- Design Name:   
-- Module Name:   F:/Courses/CS288/VHDL/Project1/Multiplier_tb.vhd
-- Project Name:  Project1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Multiplier
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
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Multiplier_tb IS
END Multiplier_tb;
 
ARCHITECTURE behavior OF Multiplier_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Multiplier
    PORT(
         a : IN  std_logic_vector(3 downto 0);
         b : IN  std_logic_vector(3 downto 0);
         product : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal a : std_logic_vector(3 downto 0) := (others => '0');
   signal b : std_logic_vector(3 downto 0) := (others => '0');

 	--Outputs
   signal product : std_logic_vector(7 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Multiplier PORT MAP (
          a => a,
          b => b,
          product => product
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
		
		--! Loop for checking multiplication
		--! Loop for varying 'a'
		for i in 0 to 15 loop
			
			--! Loop for varying 'b'
			for j in 0 to 15 loop
				
				wait for 10 ns;
				
				--! If correct product is not found, show error
				assert(product=a*b) report "Multiplication Error Detected!"
				severity error;
				
				--! In case of wrong product, increment error count
				if (product/=a*b) then
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
			report "Testbench of Multiplier completed successfully!"
			severity note;
		else
			assert true
			report "Something wrong, try again"
			severity error;
		end if;
	wait;
end process;

END;
