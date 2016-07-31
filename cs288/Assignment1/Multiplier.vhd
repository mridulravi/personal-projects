----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:06:40 03/06/2013 
-- Design Name: 
-- Module Name:    Multiplier - Behavioral 
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

entity Multiplier is
    Port ( a : in  STD_LOGIC_VECTOR (3 downto 0);							-- Multiplicand input
           b : in  STD_LOGIC_VECTOR (3 downto 0);							-- Multiplier input
           product : out  STD_LOGIC_VECTOR (7 downto 0) := "00000000");		-- Product output
end Multiplier;

architecture Behavioral of Multiplier is

component fourbitadder is
    Port ( a : in  STD_LOGIC_VECTOR (3 downto 0);							-- Augend input for 4-bit adder
           b : in  STD_LOGIC_VECTOR (3 downto 0);							-- Addend input for 4-bit adder
           sum : out  STD_LOGIC_VECTOR (3 downto 0);						-- 4 bit sum output vector
           carry : out  STD_LOGIC);											-- output carry bit
end component;


-- ti = Intermediate partial products initialised to "0000"
-- si = Partial sums of ti
-- ci = carry bits of each of the partial sums
signal t1, t2, t3, t4, t5, t6, s1, s2, s3 : std_logic_vector (3 downto 0) := "0000";
signal c1, c2, c3 : std_logic := '0'; 

begin
--instantiate and do port map for the first full adder which adds t1 and t2
adder1: fourbitadder port map (
          a => t1,
          b => t2,
			 sum => s1,
          carry => c1
        );
		  
--instantiate and do port map for the second full adder which adds t3 and t4
adder2: fourbitadder port map (
          a => t3,
          b => t4,
			 sum => s2,
          carry => c2
        );
		
--instantiate and do port map for the third full adder which adds t5 and t6
adder3: fourbitadder port map (
          a => t5,
          b => t6,
			 sum => s3,
          carry => c3
        );
		
-- instantiate partial t1
t1(0) <= a(0) and b(1);
t1(1) <= a(0) and b(2);
t1(2) <= a(0) and b(3);
t1(3) <= '0';

-- instantiate partial t2
t2(0) <= a(1) and b(0);
t2(1) <= a(1) and b(1);
t2(2) <= a(1) and b(2);
t2(3) <= a(1) and b(3);

-- instantiate partial t3
t3(0) <= s1(1);
t3(1) <= s1(2);
t3(2) <= s1(3);
t3(3) <= c1;

-- instantiate partial t4
t4(0) <= a(2) and b(0);
t4(1) <= a(2) and b(1);
t4(2) <= a(2) and b(2);
t4(3) <= a(2) and b(3);

-- instantiate partial t5
t5(0) <= s2(1);
t5(1) <= s2(2);
t5(2) <= s2(3);
t5(3) <= c2;

-- instantiate partial t6
t6(0) <= a(3) and b(0);
t6(1) <= a(3) and b(1);
t6(2) <= a(3) and b(2);
t6(3) <= a(3) and b(3);

-- generate product output
product(0) <= a(0) and b(0);
product(1) <=s1(0);
product(2) <=s2(0);
product(3) <=s3(0);
product(4) <=s3(1);
product(5) <=s3(2);
product(6) <=s3(3);
product(7) <=c3;




end Behavioral;

