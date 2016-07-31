----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:03:01 04/05/2013 
-- Design Name: 
-- Module Name:    stop_watch - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity stop_watch is
    Port ( start : in  STD_LOGIC; 		-- same input for start/stop operation, if counting is on, then causes the watch to stop, and vice versa
			  reset : in  STD_LOGIC; 		-- input to reset the stopwatch to 0 seconds
			  master_clock: in STD_LOGIC; -- system clock
			  rollover : in STD_LOGIC; 	-- input for rollover, if rollover is 1, then after 99 seconds the stopwatch goes back to 0, else it stops
           output : inout  STD_LOGIC_VECTOR (7 downto 0)); -- 8 bit output to LEDs (main output of stopwatch, coded in BCD)
end stop_watch;

architecture Behavioral of stop_watch is

	-- component for clock wizard
	component clk_wiz_v3_6 is
	port
	(-- Clock in ports
	CLK_IN1           : in     std_logic;
	-- Clock out ports
	CLK_OUT1          : out    std_logic;
	-- Status and control signals
	RESET             : in     std_logic;
	LOCKED            : out    std_logic
	);
	end component;
	
	-- component declaration of BCD counter
	component BCDcounter is
    Port ( clock : in  STD_LOGIC; -- BCD counter clock
           reset : in  STD_LOGIC; -- Reset input
           unit_d : out  STD_LOGIC_VECTOR (3 downto 0); -- units digit output
           ten_d : out  STD_LOGIC_VECTOR (3 downto 0)); -- tens digit output
	end component;
	
	signal CLK_OUT1 :std_logic :='0'; 	-- this is 5 mhz clock now we have to count 5 * 10^6 time to get it to 1 hz
	signal LOCKED :std_logic; 				-- "locked" signal for clock wizard
	signal clock1hz :std_logic:='0'; 	-- the 1 Hz clock given as input to BCD counter
	signal counter :integer := 0; 		-- counter maintained to reduce the frequency of clock to 1 Hz
	signal unit_d :std_logic_vector (3 downto 0) :=(others=>'0'); -- the units digit of stopwatch output (encoded as BCD)
	signal ten_d :std_logic_vector (3 downto 0) :=(others=>'0'); -- the tens digit of stopwatch output (encoded as BCD)
	signal state : std_logic  := '0'; 	-- the state that defines whether or not to count number of seconds (0 indicates non counting, and 1 indicates counting state)

begin
		bcd_counter:BCDCounter PORT MAP(
		reset=>Reset, 			-- input to reset the BCD counter
		clock=>clock1hz, 		-- 1 Hz clock
		unit_d=>unit_d, 		-- units digit output
		ten_d=>ten_d  			-- tens digit output
		);
	
		clock_wizard:clk_wiz_v3_6 Port Map(
		CLK_IN1=>master_clock,   -- input clock
		CLK_OUT1=>CLK_OUT1,      -- ouput clock
		RESET=>Reset,            -- reset option
		LOCKED=>LOCKED           -- locked signal
		);
	
		change:process(Reset,start,Locked,clk_out1)
			begin
				-- when reset is 1, then go to non-counting state, and reset the counter to 0
				if(reset='1') then
					state<='0';
					counter<=0;
					clock1hz<='0';
				-- when start/stop button is trigerred, then toggle between the counting and non-counting state
				elsif (start'event and start='0') then
					-- if we are not counting already, then start counting
					if (state='0') then 
						state <= '1'; --counting on
					-- if we are counting already, then stop counting
					elsif (state='1') then
						state <='0'; -- counting off
					end if;
				end if;
		
				
				if(locked='1') then
					
					if (state='1') then
						-- if rollover mode is off, then after reaching 99 seconds, the stopwatch stops (change the state to 0)
						-- if rollover mode is on, then continue counting from 0 seconds
						if (rollover='0' and output="10011001")  then
							state <='0';
						else
					-- if counting state is on, then on every rising edge of clock, increment the counter
						if(rising_edge(clk_out1)) then
							counter<= counter+1;
						end if;
						-- set the clock signal to 0 after half a second
						if(counter=2500000) then
							clock1hz<='1';
						-- set the clock signal to 1 after next half second, making the clock a 1 Hz clock							
						elsif (counter=5000000) then
							clock1hz<='0';
							counter<=0;
						end if;
					end if;
				end if;
				end if;

				
				-- give output to LEDs
				-- the first three bits of output is the tens digit of stopwatch (encoded as BCD)
				-- the last three bits of output is the ones digit of stopwatch (encoded as BCD)
				output(0)<=unit_d(0);
				output(1)<=unit_d(1);
				output(2)<=unit_d(2);
				output(3)<=unit_d(3);
				output(4)<=ten_d(0);
				output(5)<=ten_d(1);
				output(6)<=ten_d(2);
				output(7)<=ten_d(3);
				
			end process;
end Behavioral;

