SECTIONS
{
	. = 0xffff000000080000;
	.text :
	{
		KEEP(*(.text.boot))
		*(.text)
	}
	.rodata :
	{
		*(.rodata)
	}
	.data :
	{
		*(.data)
	}
	.bss ALIGN(8) (NOLOAD):
	{
		_bss_start = .;
		*(.bss)
		_bss_end = .;
	}
}

_bss_size = (_bss_end - _bss_start) >> 3;
