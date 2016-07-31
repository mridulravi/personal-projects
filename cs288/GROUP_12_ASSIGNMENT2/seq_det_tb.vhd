--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   21:16:19 04/01/2013
-- Design Name:   
-- Module Name:   C:/Users/Desktop/seq_det/seq_det_tb.vhd
-- Project Name:  seq_det
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: seq_det
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
 
ENTITY seq_det_tb IS
END seq_det_tb;
 
ARCHITECTURE behavior OF seq_det_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT seq_det
    PORT(
         clk : IN  std_logic;
         Load : IN  std_logic;
         out1 : OUT  std_logic;
         out2 : OUT  std_logic_vector(1 downto 0);
         input : IN  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal Load : std_logic := '0';
   signal input : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal out1 : std_logic;
   signal out2 : std_logic_vector(1 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: seq_det PORT MAP (
          clk => clk,
          Load => Load,
          out1 => out1,
          out2 => out2,
          input => input
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;
		
		-- loading new sequence
		load <= '1';
		input <= "10010010"; -- contains sequence 1 
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;

		-- loading new sequence
		load <= '1';
		input <= "11010101"; -- contains sequeence 2
		wait for 10 ns;

		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "01100001"; -- contains sequence 3
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "01100101"; -- contains sequence 3 
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "00100001"; -- contains sequence 1 (in continuation to the previous input)
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		
		-- loading new sequence
		input <= "10010001"; -- contains sequence 3 (in continuation to the previous input) and sequence 1
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "00011010"; -- no sequence detected
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "10101001"; -- contains sequence 2 (in continuation with previous sequence)
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
		wait for clk_period*10;
		
		-- loading new sequence
		input <= "10010011"; -- contains sequence 3 (in continuation with previous sequence) and sequence 1
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
		
		-- loading new sequence
		input <= "11101000"; -- no sequence detected
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
      
		-- loading new sequence
		input <= "00000001"; -- no sequence detetced
		load <= '1';
		wait for 10 ns;
		
		-- sending serially to sequence detector
		load <= '0';
      wait for clk_period*10;
      
		
		wait;
   end process;

END;
