--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   17:12:18 04/07/2013
-- Design Name:   
-- Module Name:   F:/Courses/CS288/VHDL/stop1/stopwatch_tb.vhd
-- Project Name:  stop1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: stop_watch
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
 
ENTITY stopwatch_tb IS
END stopwatch_tb;
 
ARCHITECTURE behavior OF stopwatch_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT stop_watch
    PORT(
         start : IN  std_logic;
         reset : IN  std_logic;
         master_clock : IN  std_logic;
         rollover : IN  std_logic;
         output : INOUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal start : std_logic := '0';
   signal reset : std_logic := '0';
   signal master_clock : std_logic := '0';
   signal rollover : std_logic := '0';

	--BiDirs
   signal output : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant master_clock_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: stop_watch PORT MAP (
          start => start,
          reset => reset,
          master_clock => master_clock,
          rollover => rollover,
          output => output
        );

   -- Clock process definitions
   master_clock_process :process
   begin
		master_clock <= '0';
		wait for master_clock_period/2;
		master_clock <= '1';
		wait for master_clock_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	
		
		-- initially rollover is on
		rollover <='1';
		
		-- start the stopwatch
		start<='1';
		wait for 10 ns;
		start <='0';
		
		-- keep it on for 50 seconds
		wait for 50000 ms;
		
		-- press the start button again to change to stop mode
      start<='1';
		wait for 10 ns;
		start <='0';
		
		-- keep it stopped for 10 seconds
		wait for 10000 ms;
      
		-- start again, count is continued from 50 seconds
		start<='1';
		wait for 10 ns;
		start <='0';
		
		-- keep it on for 55 seconds, now watch should show 5 seconds output
		wait for 55000 ms;
		
		-- reset to 0 seconds;
      reset<='1';
		wait for 10 ns;
		reset <= '0';
		wait for 10000 ms;
		
		-- start again after 10 seconds
		start <= '1';
		wait for 10 ns;
		start <='0';
		-- change the rollover mode
		rollover<= '0';
		-- keep it on for 105 seconds
		-- clock should stop at 99 seconds
		wait for 105000 ms;
      
		
		-- reset the clock to 0 seconds again
		reset<='1';
		
		
		wait;
   end process;

END;
