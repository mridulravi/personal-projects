----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:21:09 04/05/2013 
-- Design Name: 
-- Module Name:    BCDcounter - Behavioral 
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

--Entity BCDcounter counting from 0 to 99.
entity BCDcounter is
    Port ( clock : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           unit_d : out  STD_LOGIC_VECTOR (3 downto 0); --vector to store binary representation of unit's digit of the counter.
           ten_d : out  STD_LOGIC_VECTOR (3 downto 0)); --vector to store binary representation of ten's digit of the counter.
end BCDcounter;


architecture Behavioral of BCDcounter is
signal next_unit, next_ten : STD_LOGIC_VECTOR (3 downto 0):=(others=>'0'); --signals to store intermediate unit and ten's digits.
begin
	process(clock,reset) --Process triggered by clock and reset signal.
	begin
		if(reset='1') then --If reset button is pushed counter is forced to "00".
			next_unit<="0000";
			next_ten<="0000";
		elsif(rising_edge(clock)) then --On each rising edge we increment the counter.
			if(next_unit="1001") then --if unit's digit is '9', then it is set to '0' and we increment ten's digit.
				next_unit<="0000";
				if(next_ten="1001") then --if ten's digit is also '9', then it is set to '0'.
					next_ten<="0000";
				else
					next_ten<= next_ten +1;
				end if;
			else
				next_unit<=next_unit+1;
			end if;
		end if;
		unit_d<= next_unit; --Assigning values to unit and ten's digit from intermediate variables.
		ten_d<= next_ten;
	end process;
end Behavioral;

