import { useState } from 'react'
import Modal from '../components/modal/Modal'
import ClienteForm from '../components/modal/ClienteForm'

export default function ClientesPage() {
	const [open, setOpen] = useState(false)

	return (
		<div className="p-6">
			<div className="flex items-center justify-between mb-2">
				<div>
					<h1 className="text-3xl font-semibold">Clientes</h1>
					<p className="text-xl text-gray-600">Gerencie a base de clientes da barbearia</p>
				</div>

				<div>
					<button
						onClick={() => setOpen(true)}
						className="inline-flex items-center gap-2 bg-red-600 hover:bg-red-700 text-white font-semibold px-4 py-2 rounded shadow"
						aria-label="Novo Cliente"
					>
						+ Novo Cliente
					</button>
				</div>
			</div>

			<Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Cliente">
				<ClienteForm onCancel={() => setOpen(false)} onSave={() => setOpen(false)} />
			</Modal>

			{/* conteúdo da página vai aqui */}
		</div>
	)
}
