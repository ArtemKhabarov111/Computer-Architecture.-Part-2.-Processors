// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");


static uint print_count = 1; /* II. A */
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!'"); /* II. D */

/* III. Структура даних для розміщення у списку */
struct hello_item {
	struct list_head list;
	ktime_t timestamp;
};

/* IV. Статична змінна голови списку */
static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
	uint i;
	struct hello_item *item;

	/* II. B */
	if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
		pr_warn("Warning: print_count is %u (unusual value)\n",
			print_count);
	}

	/* II. C */
	if (print_count > 10) {
		pr_err("Error: print_count %u is too large (max 10)\n",
		       print_count);
		return -EINVAL;
	}

	/* Виводимо привітання print_count разів */
	for (i = 0; i < print_count; i++) {
		/* V. Виділяємо пам'ять для нового елемента списку */
		item = kmalloc(sizeof(*item), GFP_KERNEL);
		if (!item) {
			pr_err("Failed to allocate memory\n");
			return -ENOMEM;
		}

		/* Зберігаємо поточний час */
		item->timestamp = ktime_get();

		/* Додаємо елемент до списку */
		list_add_tail(&item->list, &hello_list);

		/* Друкуємо привітання */
		pr_emerg("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_item *item, *tmp;

	/* VI. Проходимо по списку з вилученням */
	list_for_each_entry_safe(item, tmp, &hello_list, list) {
		/* Виводимо час події в наносекундах */
		pr_info("Event time: %lld ns\n", ktime_to_ns(item->timestamp));

		/* Вилучаємо елемент зі списку */
		list_del(&item->list);

		/* Звільняємо пам'ять */
		kfree(item);
	}
}

module_init(hello_init);
module_exit(hello_exit);

