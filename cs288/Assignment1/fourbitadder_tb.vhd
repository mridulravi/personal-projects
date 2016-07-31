--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:00:13 03/15/2013
-- Design Name:   
-- Module Name:   F:/Courses/CS288/VHDL/Project1/fourbitadder_tb.vhd
-- Project Name:  Project1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: fourbitadder
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
 
ENTITY fourbitadder_tb IS
END fourbitadder_tb;
 
ARCHITECTURE behavior OF fourbitadder_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT fourbitadder
    PORT(
         a : IN  std_logic_vector(3 downto 0);
         b : IN  std_logic_vector(3 downto 0);
         sum : OUT  std_logic_vector(3 downto 0);
         carry : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal a : std_logic_vector(3 downto 0) := (others => '0');
   signal b : std_logic_vector(3 downto 0) := (others => '0');

 	--Outputs
   signal sum : std_logic_vector(3 downto 0);
   signal carry : std_logic;
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: fourbitadder PORT MAP (
          a => a,
          b => b,
          sum => sum,
          carry => carry
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
		
		--! Loop for checking subtraction
		--! Loop for varying 'a'
		for i in 0 to 15 loop
			
			--! Loop for varying 'b'
			for j in 0 to 15 loop
				
				wait for 10 ns;
				
				--! If correct sum is not found, show error
				assert(sum=a+b)  report "Addition Error Detected!"
				severity error;
				
				--!In case of wrong difference, increment error count
				if (sum/=a+b) then
					err_cnt:=err_cnt+1;
				end if;
			
				--! if (i+j>15) carry bit should be 1
				--! because i+j = integer(a+b)
				if (i+j>15) then
					--! show error if condition is not satisfied
					assert(carry = '1')  report "Addition Error Detected!"
					severity error;
					--! increment error count if condition is not satisfied
					if (carry/='1') then
						err_cnt:=err_cnt+1;
					end if;
				else 
					--! show error if condition is not satisfied
					assert(carry = '0')  report "Addition Error Detected!"
					severity error;
					--! increment error count if condition is not satisfied
					if (carry/='0') then
						err_cnt:=err_cnt+1;
					end if;
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
			report "Testbench of Adder completed successfully!"
			severity note;
		else
			assert true
			report "Something wrong, try again"
			severity error;
		end if;

      wait;
   end process;

END;
