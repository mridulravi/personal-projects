----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:13:10 03/06/2013 
-- Design Name: 
-- Module Name:    fulladder - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity fulladder is
    Port ( a : in  STD_LOGIC;						-- first single bit input for a  full-adder
           b : in  STD_LOGIC;						-- second single bit input for a full-adder
           c : in  STD_LOGIC;						-- third single bit input for a full-adder
           outs : out  STD_LOGIC;					-- output value for the least significant bit of the sum
           outc : out  STD_LOGIC);					-- output carry bit
end fulladder;

architecture Behavioral of fulladder is
begin
	outs <= a xor b xor c;							-- logic for output sum
	outc <= (a and b )or ( (a xor b) and c) ;		-- logic for output carry
end Behavioral;

