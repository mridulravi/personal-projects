----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:14:24 03/06/2013 
-- Design Name: 
-- Module Name:    fourbitadder - Behavioral 
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
-- use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
-- library UNISIM;
-- use UNISIM.VComponents.all;

entity fourbitadder is
    Port ( a : in  STD_LOGIC_VECTOR (3 downto 0); 				--augend input vector 
           b : in  STD_LOGIC_VECTOR (3 downto 0);				--addend input vector 
           sum : out  STD_LOGIC_VECTOR (3 downto 0);			--output sum vector 
           carry : out  STD_LOGIC);								--output carry
end fourbitadder;

architecture Behavioral of fourbitadder is
	component fulladder
	 port(
	  a:in std_logic;							-- first single bit input for a  full-adder
	  b:in std_logic;							-- second single bit input for a full-adder
	  c : in std_logic;							-- third single bit input for a full-adder
	  outc :out std_logic;						-- output value for the least significant bit of the sum
	  outs: out std_logic						-- output carry bit 
	);
	end component;
signal cin0,cin1,cin2,cin3 : std_logic:='0';	-- intermediate carries of full adders
begin
--instantiate and do port map for the first full adder.
	HA0 : fulladder port map (
          a => a(0),
          b => b(0),
          c => cin0,
          outs => sum(0),
          outc => cin1
        );
--instantiate and do port map for the second full adder.
	HA1 : fulladder port map (
		  a => a(1),
          b => b(1),
          c => cin1,
          outs => sum(1),
          outc => cin2
        );
--instantiate and do port map for the third full adder.
	HA2 : fulladder port map (
		  a => a(2),
          b => b(2),
          c => cin2,
          outs => sum(2),
          outc => cin3
        );
--instantiate and do port map for the fourth full adder.
	HA3 : fulladder port map (
		  a => a(3),
          b => b(3),
          c => cin3,
          outs => sum(3),
          outc => carry
        );
end Behavioral;