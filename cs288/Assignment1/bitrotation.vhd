----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:28:22 03/06/2013 
-- Design Name: 
-- Module Name:    bitrotation - Behavioral 
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

entity bitrotation is
    Port ( In1 : in  STD_LOGIC_VECTOR (3 downto 0);				-- Input vector
				In2: in integer;								-- Number of rotations
				dir: std_logic;									-- Left(1) or right(0) rotation
           Out1 : out  STD_LOGIC_VECTOR (3 downto 0));			-- final output vector after rotation
end bitrotation;

architecture Behavioral of bitrotation is

begin
process(In1,dir)
variable buffer1 :STD_LOGIC_VECTOR (3 downto 0);				-- a buffer that vector the output at every stage of iteration
variable temp :STD_LOGIC;
begin
	buffer1(0):=In1(0);
	buffer1(1):=In1(1);
	buffer1(2):=In1(2);
	buffer1(3):=In1(3);
	
-- Code for left rotation
-- Each bit is shifted to left and most significant bit is placed at 
-- least significant position in a single iteration
if(dir = '1') then
for i in 1 to IN2 loop
	temp:=buffer1(3);											-- a temporary variable to store the most significant value
	buffer1(3):=buffer1(2);
	buffer1(2):=buffer1(1);
	buffer1(1):=buffer1(0);
	buffer1(0):=temp;
end loop;
else 
-- Code for right rotation
-- Each bit is shifted to right and least significant bit is placed at 
-- most significant position in a single iteration
for i in 1 to IN2 loop
	temp:=buffer1(0);											-- a temporary variable to store the least significant value
	buffer1(0):=buffer1(1);
	buffer1(1):=buffer1(2);
	buffer1(2):=buffer1(3);
	buffer1(3):=temp;
end loop;
end if;
-- Direct the buffer value to the output
	Out1(0)<=buffer1(0);
	Out1(1)<=buffer1(1);
	Out1(2)<=buffer1(2);
	Out1(3)<=buffer1(3);
end process;


end Behavioral;

