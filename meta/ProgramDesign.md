---
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at https://mozilla.org/MPL/2.0/.

Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
---

# High Level Program Design

What does the program do?

* Easily enters transactions into a database (digitizes receipts)
* Keeps track of sub-accounts in general physical accounts
* Generates (displays or prints) reports
  * Transaction List, sorted/filtered by date, category, period, ...
  * Budget Reports by Period - should sum to zero
  * Generate Cash Flow Plans
  * Show Budgeted transactions
  * Show All Expenses
* Assist in Cash Flow Plans
  * Generate a Cash Flow Plan for a generic period, with option for anomalous plans for irregular purchases
  * (Reports: Cash Flow Left, Show CFP)
  * (Creator: New CFP)
* Assists in balancing
  * Bank statements with transactions
* Assists in budgeting
  * Zero-sum budget for each month using ripple-in, ripple-out
  * (Reports: Show Budget)



## Functionality in the previous MS-based system (to replicate at minimum)

| Program / File                           | Code   |
| ---------------------------------------- | ------ |
| Transactions List (MS Access)            | `TL`   |
| Cash Flow Plan (MS Excel, Printout)      | `CFP`  |
| Savings Allocations (MS Excel)           | `SA`   |
| Distributed Costs (MS Excel)             | `DC`   |
| New Feature - not implemented previously | `NEW`  |
| Calculations done by hand                | `HAND` |
| Actions needed to do online at bank      | `BANK` |
| Bank Statements                          | `BS`   |

### Create a Budget (once and at any time after)

* `DC` Distribute large costs
  * `DC` Plan Large purchases and distribute the cost over a year.
  * `DC` Display the cost per month for larger purchases.
  * `DC` Edit the total amount and the planned lifetime or cost schedule.
* `CFP` `TL` `SA` Define banking organization
  * `CFP` "Savings" is allocated, "checking" is not. Decide which other categories are allocated.
  * `CFP` `TL` Define/edit categories for transactions. Budgeted categories appear in `CFP` "Checking"
  * `CFP` `SA` Define/edit savings sub-accounts. These are reflected in `CFP` "Savings" as well as other allocated areas.
  * `SA` `CFP` Specify savings sub-accounts as hidden. No transactions displayed. Zero sum or display sum of all hidden accounts.
* `CFP` Create budget
  * `HAND` `DC` `CFP` Import prorated costs to monthly budget on `CFP ` from `DC`
  * `CFP` Define a Living expenses cap
  * `CFP` Define budget for "Checking" category
  * `CFP` Define budget for "Savings" category
  * `CFP` Define budget for essential larger categories. (either amount or percent)
  * `CFP` Define areas to direct unused income (with variable income model)

### General Monitoring. Useful at all steps

* `TL` View and edit all transactions sorted/filtered by date, period, name, amount, balanced, etc.
* `TL` View Reports for subcategories of the transactions
  * `TL` View budgeted transactions for a period
  * `TL` View all expenses, budgeted and unbudgeted
  * `TL` View all income
  * `TL` For all the above, Provide a subtotal for each (filtered by period) category
    * `TL` Especially, provide an "allocated" subtotal for each period to verify sum on CFP and SA.
* `SA` View Savings. Display the current total in all subaccounts and the cumulative total in the account after all transactions.
  * `NEW` Also Display the total that should be displayed in my bank online if everything is correct (do not include pending in the total)
  * `NEW` Show period summary for savings accounts, with the money moved from one account to another and money in/out.
* `NEW` `CFP` Display an unbudgeted amount to help with budgeting. (as budget can be changed while balancing)
* `NEW` `CFP` Allow errors in data, sums, etc, (such as budgeting more than is available) but show in red to get user to come back and fix them.
* `CFP` Edit a `CFP` after the fact (before signed) to move budgeted money from one category to another (even across "Checking" to "Savings" or bigger changes) to get it to balance. 
  * `NEW` Track `CFP` edits to score how well a budget is being followed.

### Enter all receipts

* `HAND` `SA` Add the monthly budget from `CFP` to savings accounts. This is a budgeted allocation in `TL`
* `TL` Indicate amounts as "allocated", meaning that I "spent" my income on a savings allocation in a certain subaccount.
* `TL` Enter data (interactively) into database from receipts
  * `NEW` Make "forms" for different vendors based on the receipt format. Ensure this works for income too.
  * `NEW` Make repeating transactions, which can either be completely automatic or require user intervention for, e.g., an exact amount.
  * `NEW` Allow making splits, where multiple splits, each with an amount, combine to create a transaction (with a total of zero for a zero-sum system, debits + credits).
* `SA` `TL` For transactions (i.e., splits) from savings subaccounts in `TL`, Enter specific amounts (as pending) in the appropriate subaccount and update cumulative total.
* `SA` View and edit all transactions in the savings subaccounts
  * `SA` Specifically, ensure that the balance of any subaccount does not go below zero, taking money from another account or from a budgeted category instead. Allow editing of transactions in `SA` to achieve this.
* `SA` `TL` Add transactions directly (not pending) to savings, such as savings interest.
  * `TL` Enter interest as an income transaction.
  * `TL` Also add as an allocation to `TL`, since money from income went into savings.
  * `SA` `HAND` Include savings interest in total allocated amount for the period.
* `HAND` `SA` `TL` Ensure that the unbudgeted expenses listed in `TL` are all in `SA`. Specifically makes sure the unbudgeted categories subtotals in both `TL` and `SA` match for a period.

### Balance and reconcile bank statements

* `BS` `TL` `SA` Balance Bank Statements
  * `BS` `TL` Balance transactions in bank statements with transactions made
    * `NEW` Only require balancing with transactions in `TL` dealing with a card/bank account.
  * `BS` Balance moved money between bank accounts (such as paying a credit card from checking)
  * `BS` `SA` Balance allocations - amount in banks statement will match the reconciliation amount from pending transactions in `SA`
  * `BS` `TL` `SA` Add transactions on bank statement missing from receipts. Also add to `SA` if they are unbudgeted transactions.

### Balance Period Budget

* `CFP` `SA` `TL` Compute total Living Budget used/left
  * `HAND` `CFP` `SA` Verify all amounts in `CFP` "Savings" are in `SA` period allocation.
  * `HAND` `TL` `CFP` Take the sum from each (sub)category from `TL` and list with budgeted amount in `CFP` "Checking" to compute/show over/under spent.
  * `HAND` `CFP` Calculate the over/under value for each field in the "Checking" category. Sum to over/under total. This becomes ripple-out by default.
  * `CFP` Edit `CFP` as necessary to get it to balance well for the period.
  * `HAND` `CFP` Allow funneling the ripple-out to a specific category as a sort of blow money saving account.
  * `CFP` `TL` Add remaining "Living" budget to ripple-out
  * `TL` Help setting the ripple-out and ripple-in for next month
    * `TL` Ensure that no categories exceed budgeted amount, and edit transactions (moving to miscellaneous, blow money, etc, to balance)
    * `CFP` Allow modifications to the `CFP` to get total to balance (move money from one category to another)
  * `CFP` Verify that the total "Living" budget sums to "Living Limit"
* Do full budget
  * `CFP` show total budgetable amount, containing previous months income, and previous ripple-in
    * `NEW` figure out how to robustly categorize where this months income goes before it is budgeted. (to "Slush"?)
* Verify Allocations
  * `CFP` Sum all the `CFP` allocations, from "Savings" and from other larger categories (giving, IRA, etc.)
  * `CFP` `SA` Match `CFP` allocations sum to the sum in `SA` for that period.
  * `CFP` `TL` Verify `CFP` matches `TL` allocation subtotal.
* Finish Balancing
  * `HAND` `CFP` Create a transaction while budgeting for all excess income - usually to savings or emergency fund - all expenses should equal all income.
  * `HAND` `CFP` Mark a `CFP` as done, where more edits are impossible (or at least hard - need a new revision). Sign/date the signoff.

### Periodically Update Savings Allocations (typically after budget)

* `SA` `BANK` Periodically, update `SA` pending transactions (savings has a limit of 6 withdrawals)
  * `SA` Indicate that a "reconciliation" is desired (old file used an "x" to indicate an "actual transaction")
  * `SA` Sum all the pending (outstanding) transactions. 
  * `SA` Display the cumulative amount (all pending transactions) to transfer/withdrawal to/from savings to make it come out right.
  * `BANK` Move amount specified by cumulative amount to catch up `SA` in online account.
  * `SA` Display the transfered amount to allow to balance with bank statement (pending-item reconciliation in `SA`)
  * `NEW` Display on some main display the pending transaction amount to let user know when "its time" to do a reconciliation.

