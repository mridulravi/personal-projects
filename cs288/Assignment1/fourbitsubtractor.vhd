----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:23:35 03/06/2013 
-- Design Name: 
-- Module Name:    fourbitsubtractor - Behavioral 
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

entity fourbitsubtractor is
	Port ( a : in  STD_LOGIC_VECTOR (3 downto 0);					-- minuend input vector
           b : in  STD_LOGIC_VECTOR (3 downto 0);					-- subtrahend input vector
           diff : out  STD_LOGIC_VECTOR (3 downto 0);				-- differnce output vector
           borr : out  STD_LOGIC);									-- borrow bit generated
end fourbitsubtractor;

architecture Behavioral of fourbitsubtractor is
	component fulladder
	 port(
	  a:in std_logic;											-- first single bit input for a  full-adder
	  b:in std_logic;											-- second single bit input for a full-adder
	  c : in std_logic;											-- third single bit input for a full-adder
	  outc :out std_logic;										-- output value for the least significant bit of the sum
	  outs: out std_logic										-- output carry bit
	);
	end component;
	signal cin0,cin1,cin2,cin3 : std_logic:='0';				-- intermediate carries of full adders
	signal bc0,bc1,bc2,bc3:std_logic:='0';						-- two's compliment of output vector
	signal cdash :std_logic:='0'; 								-- final carry in summing acc to complement method
																-- not(cdash) gives the real borrow c
begin
	cin0 <= '1';
	--instantiate and do port map for the first full adder.
	HA0 : fulladder port map (
          a => a(0),
          b => bc0,
          c => cin0,
          outs => diff(0),
          outc => cin1
        );
	--instantiate and do port map for the second full adder.
	HA1 : fulladder port map (
			 a => a(1),
          b => bc1,
          c => cin1,
          outs => diff(1),
          outc => cin2
        );
	--instantiate and do port map for the third full adder.
	HA2 : fulladder port map (
			 a => a(2),
          b => bc2,
          c => cin2,
          outs => diff(2),
          outc => cin3
        );
	--instantiate and do port map for the fourth full adder.
	HA3 : fulladder port map (
			 a => a(3),
          b => bc3,
          c => cin3,
          outs => diff(3),
          outc => cdash
        );
	-- taking twos compliment of output vector
	bc0 <= not(b(0));
	bc1 <= not(b(1));
	bc2 <= not(b(2));
	bc3 <= not(b(3));
	-- not of final carry in summing acc to complement method gives the real borrow
	borr   <= not(cdash);
end Behavioral;

