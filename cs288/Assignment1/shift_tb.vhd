--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:17:22 03/15/2013
-- Design Name:   
-- Module Name:   /home/anand/cs288/assignment1/shift_tb.vhd
-- Project Name:  assignment1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: shift
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
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY shift_tb IS
END shift_tb;
 
ARCHITECTURE behavior OF shift_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT shift
    PORT(
         In1 : IN  std_logic_vector(3 downto 0);
         In2 : IN  integer;
         dir : IN  std_logic;
         Out1 : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal In1 : std_logic_vector(3 downto 0) := (others => '0');
   signal In2 : integer := 0;
   signal dir : std_logic := '0';

 	--Outputs
   signal Out1 : std_logic_vector(3 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: shift PORT MAP (
          In1 => In1,
          In2 => In2,
          dir => dir,
          Out1 => Out1
        );

   -- Clock process definitions
   
   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	
		In1<="0100";
		In2<=1;
		dir<='0';
		wait for 100 ns;	
		In1<="0110";
		In2<=1;
		dir<='0';
		wait for 100 ns;	
		In1<="1100";
		In2<=1;
		dir<='1';
		wait for 100 ns;	
		In1<="1001";
		In2<=1;
		dir<='1';
		wait for 100 ns;	
		In1<="1100";
		In2<=2;
		dir<='0';
		wait for 100 ns;	
		In1<="1010";
		In2<=2;
		dir<='1';
		wait for 100 ns;	
		In1<="0010";
		In2<=3;
		dir<='0';
		wait for 100 ns;	
		In1<="0111";
		In2<=3;
		dir<='1';
		wait for 100 ns;	
		In1<="1111";
		In2<=4;
		dir<='0';
		wait for 100 ns;	
		In1<="1110";
		In2<=4;
		dir<='1';
		








      -- insert stimulus here 

      wait;
   end process;

END;
