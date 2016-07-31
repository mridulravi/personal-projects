--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   22:49:32 04/01/2013
-- Design Name:   
-- Module Name:   C:/Users/Desktop/seq_det/shift_reg_tb.vhd
-- Project Name:  seq_det
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: shift_reg
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
 
ENTITY shift_reg_tb IS
END shift_reg_tb;
 
ARCHITECTURE behavior OF shift_reg_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT shift_reg
    PORT(
         clk_s : IN  std_logic;
         load : IN  std_logic;
         parallel_input : IN  std_logic_vector(7 downto 0);
         serial_output : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal clk_s : std_logic := '0';
   signal load : std_logic := '0';
   signal parallel_input : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal serial_output : std_logic;

   -- Clock period definitions
   constant clk_s_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: shift_reg PORT MAP (
          clk_s => clk_s,
          load => load,
          parallel_input => parallel_input,
          serial_output => serial_output
        );

   -- Clock process definitions
   clk_s_process :process
   begin
		clk_s <= '0';
		wait for clk_s_period/2;
		clk_s <= '1';
		wait for clk_s_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

		-- load new sequence
      load <= '1';
		parallel_input <= "01001001";
		
		wait for 10 ns;
		
		-- serially output the sequence
		load <= '0';
		wait for clk_s_period*10;
		
		-- load new sequence
		load <= '1';
		parallel_input <= "11001101";
		
		wait for 10 ns;
		
		-- serially output the sequence
		load <= '0';
		wait for clk_s_period*10;

		-- load new sequence
		load <= '1';
		parallel_input <= "10110001";
		
		wait for 10 ns;
		
		-- serially output the sequence
		load <= '0';
		wait for clk_s_period*10;
		
      wait;
   end process;

END;
