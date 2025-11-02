import { useState } from 'react'
import Modal from '../components/modal/Modal'
import FuncionariosForm from '../components/modal/FuncionarioForm'

export default function FuncionariosPage() {
	const [open, setOpen] = useState(false)

	return (
		<div className="p-6">
			<div className="flex items-center justify-between mb-2">
				<div>
					<h1 className="text-3xl font-semibold">Funcionários</h1>
					<p className="text-xl text-gray-600">Gerencie a equipe da barbearia</p>
				</div>

				<div>
					<button
						onClick={() => setOpen(true)}
						className="inline-flex items-center gap-2 bg-red-600 hover:bg-red-700 text-white font-semibold px-4 py-2 rounded shadow"
						aria-label="Novo Funcionário"
					>
						+ Novo Funcionário
					</button>
				</div>
			</div>

			<Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Funcionário">
				<FuncionariosForm onCancel={() => setOpen(false)} onSave={() => setOpen(false)} />
			</Modal>

			{/* conteúdo da página vai aqui */}
		</div>
	)
}
