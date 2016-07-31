----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    04:57:46 03/06/2013 
-- Design Name: 
-- Module Name:    BitwiseOperations - Behavioral 
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

entity BitwiseOperations is
    Port ( a : in  STD_LOGIC_VECTOR (3 downto 0);				-- first input vector
           b : in  STD_LOGIC_VECTOR (3 downto 0);				-- second input vector
           bitwise_and : out  STD_LOGIC_VECTOR (3 downto 0);	-- output vector after generating doing A.B	
           bitwise_or : out  STD_LOGIC_VECTOR (3 downto 0);		-- output vector after generating doing A+B	
           bitwise_xor : out  STD_LOGIC_VECTOR (3 downto 0));	-- output vector after generating doing A XOR B	
end BitwiseOperations;

architecture Behavioral of BitwiseOperations is

begin
	process(a,b)
	begin
	 for i in 0 to 3 loop
		bitwise_and(i) <= a(i) and b(i);						-- Do bitwise AND
		bitwise_or(i) <= a(i) or b(i);							-- Do bitwise OR
		bitwise_xor(i) <= a(i) xor b(i);						-- Do bitwise XOR 
	end loop;
	end process;
end Behavioral;

