using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_part
{
    internal static class Operations
    {
        // Arithmetics
        public static decimal Sum(decimal left_operand, decimal right_operand)
        {
            return (left_operand + right_operand);
        }
        public static decimal Sub(decimal left_operand, decimal right_operand)
        {
            return (left_operand - right_operand);
        }
        public static decimal Mul(decimal left_operand, decimal right_operand)
        {
            return (left_operand * right_operand);
        }
        public static decimal Div(decimal left_operand, decimal right_operand)
        {
            return (left_operand / right_operand);
        }
        public static decimal Mod(decimal left_operand, decimal right_operand)
        {
            return (left_operand % right_operand);
        }
        // Comparison
        public static int Less(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand < rigth_operand) ? 1 : 0;
        }
        public static int LessEq(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand <= rigth_operand) ? 1 : 0;
        }
        public static int Greater(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand > rigth_operand) ? 1 : 0;
        }
        public static int GreaterEq(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand >= rigth_operand) ? 1 : 0;
        }
        public static int Equal(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand == rigth_operand) ? 1 : 0;
        }
        public static int NotEqual(decimal left_operand, decimal rigth_operand)
        {
            return (left_operand != rigth_operand) ? 1 : 0;
        }
        // Other
        public static decimal Negate(decimal operand)
        {
            return operand * -1;
        }
        public static decimal Floor(decimal operand)
        {
            return Math.Floor(operand);
        }
        public static decimal Truncate(decimal operand)
        {
            return Math.Truncate(operand);
        }
        public static decimal Round(decimal operand)
        {
            return Math.Round(operand, MidpointRounding.AwayFromZero);
        }
    }
}
